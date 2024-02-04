#include"display_window.hpp"
#include"main_window.hpp"
#include"debug_window.hpp"
#include"toolbox_window.hpp"
#include"record_window.hpp"
#include<QPainter>
#include<QIcon>
#include<QDateTime>
#include<QMessageBox>
#include"new_filter.hpp"
#include"control_window.hpp"

DisplayWindow::DisplayWindow(QWidget *parent) : QDialog(parent) {
    setGeometry(700, 0, 640, 480);
    setWindowTitle("Display Window");
    setWindowIcon(QIcon(":/images/icon.png"));
    
    image_label = new QLabel(this);
    image_label->setGeometry(0, 0, 640, 480);
    // don't use debug_window not initalized yet
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutFunc()));
    //setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}

void DisplayWindow::closeEvent(QCloseEvent *) {
    main_window->toolbox_window->setShow();
}


void DisplayWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}

void DisplayWindow::setDebugWindow(DebugWindow *d) {
    debug_window = d;
}


void DisplayWindow::setSourceImage(const cv::Mat &src) {
    source_image = src.clone();
    display(source_image);
}

void DisplayWindow::paintEvent(QPaintEvent *) {
    if(!source_image.empty() || cap.isOpened() == true) {
        QPainter paint(this);
        paint.fillRect(QRect(QPoint(0, 0), size()), QColor(0,0,0));
    }
}

void DisplayWindow::display(QImage &image) {
    QRect src(QPoint(0, 0), size());
    QPixmap p = QPixmap::fromImage(image).scaled(size(),Qt::KeepAspectRatio, Qt::FastTransformation);
    QRect dst(QPoint(0,0),p.size());
    dst.moveCenter(src.center());
    image_label->setGeometry(dst);
    image_label->setPixmap(p);
} 

void DisplayWindow::display(const cv::Mat &src) {
    main_window->setInfo(src);
    QImage image = Mat2QImage(src);
    display(image);
}

void DisplayWindow::startAnimation() {
    timer->start(static_cast<int>((double)1000 / this->fps));
    debug_window->Log("gui: Animation restarted.\n");
}

void DisplayWindow::startAnimation(float fps) {
    this->fps = fps;
    timer->start(static_cast<int>((double)1000 / fps));
    main_window->toolbox_window->setStopText();
    main_window->enableRecord();
}

void DisplayWindow::stopAnimation() {
    timer->stop();
    debug_window->Log("gui: Animation stopped\n");
    main_window->toolbox_window->setStopText();
    //main_window->stopRecording();
}

void DisplayWindow::resetFrameCount() {
    frame_count = 0;
}


void DisplayWindow::setCurrentFilter(const std::string &f) {
    if(fade_on) {
        fade_filter = current_filter;
        fade = true;
        fade_f = 0.5;
    }
    if(current_filter.find("New_") != std::string::npos) {
        New_CallFilterClear(current_filter);
    }
    current_filter = f;
    /// release objects
    ac::release_all_objects();
    QString text;
    QTextStream stream(&text);
    if(f.length() > 0) {
        stream << "glitch: Current filter set to: " << f.c_str() << "\n";
        debug_window->Log(text);
    }
}

QString DisplayWindow::getCurrentFilter() const { return current_filter.c_str(); }
double DisplayWindow::getCurrentFPS() const { return this->fps; }
InputMode DisplayWindow::getCurrentInputMode() const { return mode; }
QString DisplayWindow::getCurrentInputModeString() const {
    if(mode == InputMode::IMAGE) return "Image";
    return "Video";
}
QString DisplayWindow::getPrefix() const { return prefix; }
QString DisplayWindow::getDirPath() const { return outdir; }
cv::VideoCapture &DisplayWindow::getCap() { return cap; }
size_t DisplayWindow::getFrameCount() const { return frame_count; }

void DisplayWindow::takeSnapshot(const QString &filename, const QString &file_type) {
    QString text;
    QTextStream stream(&text);
    QDateTime now = QDateTime::currentDateTime();
    QString time_data = now.toString();
    for(int i = 0; i < time_data.length(); ++i) {
        if(time_data[i] == '/' || time_data[i] == ' ' || time_data[i] == ':') time_data[i] = '.';
    }
    stream << filename << time_data << "-" << image.cols << "x" << image.rows << "." << file_type;
    cv::imwrite(text.toStdString(), image);
    QString textx;
    QTextStream streamx(&textx);
    streamx << "glitch: Took snapshot: " << text << "\n";
    debug_window->Log(textx);
}

void DisplayWindow::setSource() {
    source_image = image.clone();
    if(undo_list.size() < 25)
        undo_list.push_back(source_image.clone());
    else {
        undo_list.push_back(source_image.clone());
        undo_list.pop_front();
    }
    display(source_image);
    QString text;
    QTextStream stream(&text);
    stream << "glitch: Set current frame as Source image.\n";
    debug_window->Log(text);
}

void DisplayWindow::step() {
    timeoutFunc();  
}

void DisplayWindow::setVideoIndex(int pos) {
    if(!timer->isActive() && cap.isOpened()) {
        frame_count = pos;
        cap.set(cv::CAP_PROP_POS_FRAMES, pos);
        timeoutFunc();
    }
}


void DisplayWindow::timeoutFunc() {

  frame_count ++;

    if(mode == InputMode::IMAGE)
        image = source_image.clone();
    else if(mode == InputMode::VIDEO) {
        cv::Mat m;

        if(cap.read(m)) {
            image = m;
            int pos = cap.get(cv::CAP_PROP_POS_FRAMES);
            main_window->control_window->setPos(pos);
        } else {

            if(repeat == true) {
            // rewind
                cap.open(input_filename);
                if(!cap.isOpened()) {
                    // error message
                    QMessageBox box;
                    box.setWindowTitle("Error opening video file");
                    box.setText("Error opening video file...\n");
                    box.setIcon(QMessageBox::Icon::Warning);
                    box.exec();
                    stopAnimation();
                    main_window->disableUndo();
                } 
    
                int max = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));
                main_window->control_window->enableControl(0, max);
                main_window->control_window->setPos(0);
                frame_count = 0;
            } else {
                stopAnimation();
                main_window->stopRecording();
                main_window->disableUndo();
                main_window->toolbox_window->setStartText();
                cap.open(input_filename);
                if(!cap.isOpened()) {
                    QMessageBox box;
                    box.setWindowTitle("Error opening video file");
                    box.setText("Error opening video file...\n");
                    box.setIcon(QMessageBox::Icon::Warning);
                    box.exec();
                }
                cap.read(image); 
                frame_count = 0;             
            }
        }
    }

    cv::Mat final_image;
       
    if(current_filter != "") {
        if(fade) final_image = image.clone();

        if(first_filter != "None")
            New_CallFilter(first_filter, image);
    
        New_CallFilter(current_filter, image);
        setColorOffset(image);
    }
    
    if(fade && !final_image.empty()) {        
        if(fade_filter.length() > 0)
            New_CallFilter(fade_filter, final_image);
        
        ac::AlphaBlend(image, final_image, image, fade_f);
        fade_f += 0.1;
        if(fade_f >= 1.0) {
            fade_f = 0.5;
            fade = false;
        }
        display(image);
        if(save_png_file == true) {
            std::ostringstream stream;
            stream << png_path << "/" << "png.stream." << std::setfill('0') << std::setw(10) << png_count++ << ".png";
            cv::imwrite(stream.str(), image);

        } else {
            if(main_window->isFileOpen())
               main_window->writeFrame(image);
        }

    } else {
        display(image);
        if(save_png_file == true) {
            std::ostringstream stream;
            stream << png_path << "/" << "png.stream." << std::setfill('0') << std::setw(10) << png_count++ << ".png";
            cv::imwrite(stream.str(), image);

        } else {
            if(main_window->isFileOpen())
               main_window->writeFrame(image);
        }
    }
}

void DisplayWindow::reset() {
    if(cap.isOpened()) {
        cap.set(cv::CAP_PROP_POS_FRAMES, 0);
        frame_count = 0;

    }
}

void DisplayWindow::setColorOffset(const cv::Vec3b &color) {
    color_offset[0] = color[0];
    color_offset[1] = color[1];
    color_offset[2] = color[2];
    QString text;
    QTextStream stream(&text);
    stream << "glitch: color offset toggled; " << int(color[0]) << "," << int(color[1]) << "," << int(color[2]) << "\n";
    debug_window->Log(text);
}

void DisplayWindow::setColorOffset(cv::Mat &frame) {
    for(int z = 0; z < frame.rows; ++z) {
        for(int i = 0; i < frame.cols; ++i) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            // wrapping add
            pixel[0] += color_offset[0];
            pixel[1] += color_offset[1];
            pixel[2] += color_offset[2];
        }
    }
}

void DisplayWindow::setFilterFirst(const std::string &first) {
    first_filter = first;
}

void DisplayWindow::keyPressEvent(QKeyEvent *e) {
    switch(e->key()) {
        case Qt::Key_Up:
            if(main_window != nullptr)
                main_window->keyShiftUp();
            
            break;
        case Qt::Key_Down:
            if(main_window != nullptr)
                main_window->keyShiftDown();
            
            break;
        case Qt::Key_S: {
            if(outdir != "") {
                static int snap_index = 0;
                QString text;
                QTextStream stream(&text);
                stream << outdir << "/" << prefix << "-snap-" << ++snap_index << "-";
                takeSnapshot(text, "png");
            }
        }
            break;
        case Qt::Key_A: {
            if(main_window != nullptr && mode == InputMode::IMAGE)
                main_window->toolbox_window->setSource();
            
        }
            break;
        case Qt::Key_E: {
            if(main_window != nullptr) {
                main_window->toolbox_window->stepAction();
            }
        }
            break;
        case Qt::Key_D: {
            if(main_window != nullptr) {
                main_window->toolbox_window->stopAction();
            }           
        }
            break;
    }
}

void DisplayWindow::setPrefix(const QString &dir, const QString &p) {
    outdir = dir;
    prefix = p;
}
void DisplayWindow::undo() {
    
    if(!undo_list.empty()) {
        QString text;
        QTextStream stream(&text);
        stream << "gui: Undo list of size: " << undo_list.size() << " popped.\n";
        redo_list.push_back(undo_list.back().clone());
        source_image = undo_list.back().clone();
        display(source_image);
        undo_list.pop_back();
        debug_window->Log(text);
    }
}

void DisplayWindow::redo() {
    if(!redo_list.empty()) {
        QString text;
        QTextStream stream(&text);
        stream << "gui: Redo list of size: " << redo_list.size() << " popped.\n";
        source_image = redo_list.back().clone();
        display(source_image);
        redo_list.pop_back();
        debug_window->Log(text);
    }
}

void DisplayWindow::record() {
    main_window->recordVideo();
}

bool DisplayWindow::recording() {
    return main_window->isFileOpen();
}

void DisplayWindow::savePNG(bool on, std::string path) {
    save_png_file = on;
    png_count = 0;
    png_path = path;
}

bool DisplayWindow::resetInputMode(const InputMode &m, std::string source_file) {
    mode = m;
    input_filename = source_file;
    if(mode == InputMode::IMAGE) {
        if(cap.isOpened()) {
            cap.release();
        }
        source_image = cv::imread(input_filename);
        if(source_image.empty()) {
            QMessageBox box;
            box.setWindowTitle("Error could not load image");
            box.setIcon(QMessageBox::Icon::Warning);
            box.setText("Could not load image");
            box.exec(); 
            return false;
        }
        
    } else if(mode == InputMode::VIDEO) {
        main_window->disableUndo();
        if(cap.isOpened()) {
            cap.release();
        }
        cap.open(source_file);
        if(!cap.isOpened()) {
            // error message
            QMessageBox box;
            box.setWindowTitle("Error opening video file");
            box.setText("Error opening video file...\n");
            box.setIcon(QMessageBox::Icon::Warning);
            box.exec();
            stopAnimation();
            return false;         
        } else {
           if(main_window->record_window->rec_info.load_start == true)
                main_window->record();

            int max = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));
            main_window->control_window->enableControl(0, max);
            main_window->control_window->setPos(0);
          
        }
    }
    return true;
}

void DisplayWindow::setInputMode(const InputMode &m) {
    mode = m;
}

void DisplayWindow::setFade(bool value) {
    fade_on = value;
}

void DisplayWindow::clear_undo() {
   if(!undo_list.empty())
        undo_list.erase(undo_list.begin(), undo_list.end());

   if(!redo_list.empty())
        redo_list.erase(redo_list.begin(), redo_list.end());
    
}

bool DisplayWindow::getResolution(int &w, int &h) {
    if(mode == InputMode::VIDEO) {
        if(cap.isOpened()) {
            w = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
            h = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
            return true;   
        }
    } else {
         w = source_image.cols;
         h = source_image.rows;
         return true;
    }
    return false;
}

float DisplayWindow::videoFPS() {
    return static_cast<float>(cap.get(cv::CAP_PROP_FPS));
}

void DisplayWindow::setRepeat(bool r) {
    repeat = r;
}

void DisplayWindow::closeVideo() {
    if(cap.isOpened()) {
        cap.release();
    }
}

std::ostream &operator<<(std::ostream &out, const InputMode &im) {
    if(im == InputMode::VIDEO)
        out << "Video";
    else if(im == InputMode::IMAGE)
        out << "Image";
    return out;
}