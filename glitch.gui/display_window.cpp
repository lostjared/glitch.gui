#include"display_window.hpp"
#include"main_window.hpp"
#include"debug_window.hpp"
#include"toolbox_window.hpp"
#include<QPainter>
#include<QIcon>
#include<QDateTime>
#include<QMessageBox>
#include"new_filter.hpp"


DisplayWindow::DisplayWindow(QWidget *parent) : QDialog(parent) {
    setGeometry(700, 0, 640, 480);
    setWindowTitle("Display Window");
    setWindowIcon(QIcon(":/images/icon.png"));

    image_label = new QLabel(this);
    image_label->setGeometry(0, 0, 640, 480);
    // don't use debug_window not initalized yet
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutFunc()));
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
}

void DisplayWindow::stopAnimation() {
    timer->stop();
    debug_window->Log("gui: Animation stopped\n");
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
    stream << "glitch: Current filter set to: " << f.c_str() << "\n";
    debug_window->Log(text);
}

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
    stream << "glitch: Set current frame as Source image\n";
    debug_window->Log(text);
}

void DisplayWindow::step() {
    timeoutFunc();
    QString text;
    QTextStream stream(&text);
    stream << "glitch: Took step.\n";
    debug_window->Log(text);    
}

void DisplayWindow::timeoutFunc() {
    if(mode == InputMode::IMAGE)
        image = source_image.clone();
    else if(mode == InputMode::VIDEO) {
        cv::Mat m;
        if(cap.read(m)) {
            image = m;
        } else {
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
        }
    }

    cv::Mat final_image;
    if(fade) final_image = image.clone();

    if(first_filter != "None")
        New_CallFilter(first_filter, image);

    New_CallFilter(current_filter, image);
    setColorOffset(image);

    if(fade && !final_image.empty()) {        
        if(fade_filter.length() > 0)
            New_CallFilter(fade_filter, final_image);

        ac::AlphaBlend(image, final_image, image, fade_f);
        fade_f += 0.1;
        if(fade_f >= 1.0) {
            fade_f = 0.5;
            fade = false;
        }
        std::cout << "HERE!: "<< fade_f << ":" << fade_filter <<"\n";
        display(image);
    } else {
        display(image);
    }
    update();
}

void DisplayWindow::setColorOffset(const cv::Vec3b &color) {
    color_offset = color;
    debug_window->Log("glitch: color offset toggled.\n");
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
            if(main_window != nullptr)
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

bool DisplayWindow::resetInputMode(const InputMode &m, std::string source_file) {
    mode = m;
    input_filename = source_file;
    if(mode == InputMode::IMAGE) {
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
