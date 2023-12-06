#include "main_window.hpp"
#include<QMenuBar>
#include<QFileDialog>
#include<QPainter>
#include<QMessageBox>
#include"toolbox_window.hpp"
#include"display_window.hpp"
#include"new_image.hpp"
#include"debug_window.hpp"
#include"record_window.hpp"
#include"cat_vec.hpp"
#include"new_filter.hpp"
#include"filters/filters.hpp"
#include<cctype>
#include<cstring>
#include"ffmpeg_write.h"
#include<QDir>
#include<algorithm>
#include"custom_window.hpp"

cv::Mat QImage2Mat(QImage const& src)
{
    cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
    cv::Mat result;
    cvtColor(tmp, result,cv::COLOR_BGR2RGB);
    return result;
}

QImage Mat2QImage(cv::Mat const& src)
{
    cv::Mat temp;
    cvtColor(src, temp,cv::COLOR_BGR2RGB);
    QImage dest((const uchar *) temp.data, static_cast<int>(temp.cols), static_cast<int>(temp.rows), static_cast<int>(temp.step), QImage::Format_RGB888);
    dest.bits();
    return dest;
}

MainWindow::MainWindow()  {
    ac::init();
    build_lists();
    ac::setMaxAllocated(325);
    debug_window = new DebugWindow(this);
    debug_window->show();
    
    toolbox_window = new ToolboxWindow(this);
    toolbox_window->setGeometry(100,100,250,400);
    toolbox_window->setMainWindow(this);
    toolbox_window->show();
    
    display_window = new DisplayWindow(this);
    display_window->setMainWindow(this);
    display_window->setGeometry(700, 100, 800, 600);
    display_window->hide();
    display_window->setDebugWindow(debug_window);
    
    toolbox_window->setDisplayWindow(display_window);
    
    newimage_window = new NewImageWindow(this);
    newimage_window->setGeometry(1000, 100, 320, 240);
    newimage_window->setMainWindow(this);
    newimage_window->hide();
    
    record_window = new RecordWindow(this);
    record_window->setMainWindow(this);
    record_window->hide();

    toolbox_window->setRecordWindow(record_window);

    custom_window = new CustomWindow(this);
    custom_window->hide();

    setFixedSize(640, 360);
    setWindowTitle(tr(APP_NAME));
    file_menu = menuBar()->addMenu(tr("&File"));
    file_open = new QAction(tr("&Create New Art"), this);
    file_open->setShortcut(tr("Ctrl+N"));
    connect(file_open, SIGNAL(triggered()), this, SLOT(openFile()));
    file_menu->addAction(file_open);
    
    edit_menu = menuBar()->addMenu(tr("&Edit"));
    edit_undo = new QAction(tr("Undo"), this);
    edit_undo->setShortcut(tr("Ctrl+Z"));
    edit_undo->setEnabled(false);
    
    connect(edit_undo, SIGNAL(triggered()), this, SLOT(editUndo()));
    
    edit_menu->addAction(edit_undo);
    
    edit_redo = new QAction(tr("Redo"), this);
    edit_redo->setShortcut(tr("Shift+Ctrl+Z"));
    edit_redo->setEnabled(false);
    
    connect(edit_redo, SIGNAL(triggered()), this, SLOT(editRedo()));
    
    edit_menu->addAction(edit_redo);

    record_menu = menuBar()->addMenu(tr("&Record"));

    record_set = new QAction(tr("Record Settings"), this);
    record_set->setShortcut(tr("Ctrl+S"));
    record_set->setEnabled(true);

    record_menu->addAction(record_set);

    record_rec = new QAction(tr("Record"), this);
    record_rec->setShortcut(tr("Ctrl+R"));
    record_rec->setEnabled(false);

    record_menu->addSeparator();

    record_menu->addAction(record_rec);

    record_menu->addSeparator();

    record_repeat = new QAction(tr("Repeat"), this);
    record_repeat->setShortcut(tr("Ctrl+U"));
    record_repeat->setCheckable(true);
    record_repeat->setChecked(false);
    record_menu->addAction(record_repeat);

    connect(record_repeat, SIGNAL(triggered()), this, SLOT(toggle_repeat()));
    connect(record_set, SIGNAL(triggered()), this, SLOT(showRecord()));
    connect(record_rec, SIGNAL(triggered()), this, SLOT(recordVideo()));  

    image_menu = menuBar()->addMenu(tr("&Image"));
    image_save = new QAction(tr("&Save"));
    image_save->setShortcut(tr("Ctrl+S"));
    image_save->setEnabled(false);

    image_menu->addAction(image_save);

    image_step = new QAction(tr("S&tep"));
    image_step->setShortcut(tr("Ctrl+T"));
    image_step->setEnabled(false);

    image_menu->addAction(image_step);

    image_set_source = new QAction(tr("S&et Source"));
    image_set_source->setShortcut(tr("Ctrl+E"));
    image_set_source->setEnabled(false);

    image_menu->addAction(image_set_source);

    image_ani = new QAction(tr("Stop Animation"));
    image_ani->setShortcut(tr("Ctrl+Z"));
    image_ani->setEnabled(false);

    image_menu->addAction(image_ani);

    connect(image_save, SIGNAL(triggered()), this, SLOT(image_Save()));
    connect(image_step, SIGNAL(triggered()), this, SLOT(image_Step()));
    connect(image_set_source, SIGNAL(triggered()), this, SLOT(image_Set()));
    connect(image_ani, SIGNAL(triggered()), this, SLOT(image_Ani()));

    filter_menu = menuBar()->addMenu(tr("&Filter"));
    filter_custom = new QAction(tr("Custom Filter"), this);
    filter_custom->setShortcut(tr("CtrL+C"));

    connect(filter_custom, SIGNAL(triggered()), this, SLOT(filter_Show()));
    
    filter_menu->addAction(filter_custom);

    filter_edit = new QAction(tr("Remove Custom"));

    connect(filter_edit, SIGNAL(triggered()), this, SLOT(filter_Edit()));

    filter_menu->addAction(filter_edit);

    help_menu = menuBar()->addMenu(tr("&Help"));
    help_about = new QAction(tr("&About"), this);
    connect(help_about, SIGNAL(triggered()), this, SLOT(helpAbout()));
    help_menu->addAction(help_about);
    
    setGeometry(375,100,640,480);
    
    filter_cat = new QComboBox(this);
    filter_cat->setGeometry(15, 35, 300, 25);
    
    filter_cat->addItem(tr("In order"));
    filter_cat->addItem(tr("Sorted"));
    filter_cat->addItem(tr("Fast"));
    filter_cat->addItem(tr("Glitch"));
    filter_cat->addItem(tr("Mirror"));
    filter_cat->addItem(tr("New Filter"));
    filter_cat->addItem(tr("Custom"));
    
    connect(filter_cat, SIGNAL(currentIndexChanged(int)), this, SLOT(catIndexChanged(int)));
    
    filter_list = new QComboBox(this);
    filter_list->setGeometry(15, 35+35, 300, 25);
    connect(filter_list, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));
    filter_list->setEnabled(true);
    
    filter_list_view = new QListWidget(this);
    filter_list_view->setGeometry(15, 35+25+10+35, 300, 200);
    
    filter_search = new QLineEdit(this);
    filter_search->setGeometry(300+15+10, 35, 300-75, 30);
    connect(filter_search, SIGNAL(returnPressed()), this, SLOT(searchFilter()));
    
    filter_search_button = new QPushButton(tr("Search"), this);
    filter_search_button->setGeometry(300+15+10+225+10, 35, 70, 30);
    
    connect(filter_search_button, SIGNAL(clicked()), this, SLOT(searchFilter()));
    
    filter_search_set = new QPushButton(tr("Select"), this);
    filter_search_set->setGeometry(15, 35+25+10+200+10+35, 70, 30);
    
    connect(filter_search_set, SIGNAL(clicked()), this, SLOT(setSearch()));
    
    filter_first_set = new QPushButton(tr("&First"), this);
    filter_first_set->setGeometry(15+70+10, 35+25+10+200+10+35, 70, 30);
    
    connect(filter_first_set, SIGNAL(clicked()), this, SLOT(firstSet()));
    
    filter_first_clear = new QPushButton(tr("&Clear"), this);
    filter_first_clear->setGeometry(15+70+10+70+10, 35+25+10+200+10+35, 70, 30);
    
    connect(filter_first_clear, SIGNAL(clicked()), this, SLOT(firstClear()));
    
    filter_list_view->setEnabled(true);
    filter_search->setEnabled(true);
    filter_search_button->setEnabled(true);
    filter_search_set->setEnabled(true);
    filter_cat->setEnabled(true);
    filter_first_set->setEnabled(true);
    filter_first_clear->setEnabled(true);
    
    filter_first = new QLabel(tr("First: None"), this);
    filter_first->setGeometry(315+10, 35+25+10+35, 200, 30);

    content_data = new QTextEdit(this);
    content_data->setGeometry(315+10,135,300,165); 
    content_data->setReadOnly(true);
    content_data->setText("Content-Data");
    
    init_filter_list();
    init_filters_local();
    update_new_filter_map();
    loadCategory(0);
    setWindowIcon(QIcon(":/images/icon.png"));
    display_window->setFilterFirst("None");
    debug_window->Log("gui: successfully initalized\n");
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

}

void MainWindow::loadCategory(int index) {
    filter_list->clear();
    if(index == 5) {
        auto *a = &new_filter_list;
        for(int i = 0; i < static_cast<int>(a->size()); ++i) {
            filter_list->addItem(a->at(i).name);
        }
    } else if(index == 6) {
        auto *a = &cat_custom;
        for(int i = 0; i < static_cast<int>(a->size()); ++i) {
            filter_list->addItem(a->at(i).first.c_str());
        }  
    } else {
        std::vector<std::string> *v = vec_cat[index];
        for(int i = 0; i < static_cast<int>(v->size()); ++i) {
            std::string s = v->at(i);
            if(s.find("InOrder") == std::string::npos)
                filter_list->addItem(v->at(i).c_str());
        }
    }
    filter_list_view->clear();
    filter_list->setCurrentIndex(0);
}

QString MainWindow::contentData(const std::string &fn, const cv::Mat &frame) {
    QString text;
    QTextStream stream(&text);

    if(isFileOpen())
        stream << "[ Recording ] - ";

    stream << "path [" << fn.c_str() << "]" << "\n info [" << frame.cols << "x" << frame.rows << " channels: " << frame.channels() << "]\n";
    return text;
}

void MainWindow::showRecord() {
    record_window->show();
}

void MainWindow::recordVideo() {
    if(record_rec->text() == tr("Record")) {
        // start recording
        record();
    } else {
        record_rec->setText(tr("Record"));
        toolbox_window->setRecordText(true);
        // stop recording
        stopRecording();
    }
}

void MainWindow::stopRecording() {
   if(file_stream != NULL) {
#ifdef _WIN32
        _pclose(file_stream);
#else
        pclose(file_stream);
#endif
        file_stream = NULL;
        QString output;
        QTextStream stream(&output);
        stream << "glitch: Stopped recording...\n";
        debug_window->Log(output); 
    } else if(record_window->rec_info.save_png == true) {
        display_window->savePNG(false, "");
        debug_window->Log("glitch: Stopping PNG sequence\n");
    } 
}

void MainWindow::record() {


    RecordInfo &info = record_window->rec_info;

    if(info.save_png == true) {
        display_window->savePNG(true, info.filename);
        QString text;
        QTextStream stream(&text);
        stream << "glitch: Now writing PNG sequence to: " << info.filename.c_str() << "\n";
        debug_window->Log(text);
        record_rec->setText(tr("Stop Recording"));
        toolbox_window->setRecordText(false);
    } else if(file_stream == NULL && record_window->rec_info_set) {
        if(info.save_png == false) {
            std::ostringstream res;
            int width = 0, height = 0;
            if(display_window->getResolution(width, height)) {
                res << width << "x" << height;
                info.dst = res.str();
                info.src = res.str();
            }    
            QString fps = info.fps.c_str();
            if(info.fps == "same") {
                fps = "";
                QTextStream stream(&fps);
                stream << display_window->getCurrentFPS();
            }
            static int index = 1;
            std::ostringstream filename;
            filename << info.filename << "/" << "Video" << index++ << ".mp4";
            ffmpeg_path = info.ffmpeg_path;
            #ifdef _WIN32
            QDir d(".");
            ffmpeg_path = d.absoultePath().toStdString() + "/ffmpeg.exe";
            #endif
            if(startRecording(filename.str().c_str(), info.codec.c_str(), info.src.c_str(), info.dst.c_str(), info.crf.c_str(), fps)) {
                record_rec->setText(tr("Stop Recording"));
                toolbox_window->setRecordText(false);
                QString output;
                QTextStream stream(&output);
                stream << "glitch: Now recording to " << filename.str().c_str() << " @ " << info.fps.c_str() << " / " << info.codec.c_str() << " / CRF: " << info.crf.c_str() << "\n";
                debug_window->Log(output); 
            }   
        } 
     } else {
        QMessageBox msgbox;
        msgbox.setIcon(QMessageBox::Icon::Critical);
        msgbox.setWindowIcon(QIcon(":/images/icon.png"));
        msgbox.setWindowTitle(tr("Error didn't set Record info"));
        msgbox.setText(tr("Please fill out the recording information before recording...\n"));
        msgbox.exec();
    }
}

bool MainWindow::startRecording(const QString &filename, const QString &codec_type, const QString &res, const QString &dst_res, const QString &crf, const QString &fps) {
    if(file_stream == NULL) {
        file_stream = open_ffmpeg(filename.toStdString().c_str(), codec_type.toStdString().c_str(),res.toStdString().c_str(), dst_res.toStdString().c_str(), fps.toStdString().c_str(), crf.toStdString().c_str());
        if(!file_stream) {
            std::cerr << "Could not open pipe to FFmpeg\n";
            QMessageBox msgbox;
            msgbox.setIcon(QMessageBox::Icon::Critical);
            msgbox.setWindowIcon(QIcon(":/images/icon.png"));
            msgbox.setWindowTitle(tr("Error on opening pipe"));
            msgbox.setText(tr("Could not open pipe to ffmpeg. Is it installed and path set?"));
            msgbox.exec();
            return false;
        }
    }
    return true;
}

void MainWindow::writeFrame(cv::Mat &frame) {
    if(file_stream != NULL) {
        write_ffmpeg(file_stream, frame);
    }
}

bool MainWindow::isFileOpen() {
    if(file_stream != NULL)
        return true;
    return false;
}

void MainWindow::enableRecord() {
    record_rec->setEnabled(true);
}

void MainWindow::setInfo(const cv::Mat &frame) {
    QString data = contentData(cur_filename, frame);
    QTextStream stream(&data);
    stream << "Frame Index: " << display_window->getFrameCount() << "\n";
    stream << "Input Mode: [" << display_window->getCurrentInputModeString() << "]\n";
    stream << "Current Filter: " << display_window->getCurrentFilter() << "\n";
    stream << "Current FPS: " << display_window->getCurrentFPS() << "\n";
    if(display_window->getCap().isOpened()) {
        double fps_ = display_window->getCap().get(cv::CAP_PROP_FPS);
        stream << "Video stream FPS: " << fps_ << "\n";
        double fc_ = display_window->getCap().get(cv::CAP_PROP_FRAME_COUNT);
        stream << "Video stream Frame Count: " << static_cast<int>(fc_) << "\n";
        double per = static_cast<double>(display_window->getFrameCount())/fc_ * 100.00;
        stream << " Video stream: " << static_cast<int>(per) << "%\n";
    }
    content_data->setText(data);
}

void MainWindow::startNewAnimation(const QString &filename, const QString &outdir, const QString &prefix, float fps) {
    if(filename != "") {
        auto lwr = [](const std::string &text) {
            std::string ftext;
            for(std::string::size_type i = 0; i < text.length(); ++i) {
                char c = tolower(text[i]);
                ftext += c;
            }
            return ftext;
        };

        std::string filename_chk = lwr(filename.toStdString());
        if(filename_chk.find(".avi") != std::string::npos || filename_chk.find(".mov") != std::string::npos || filename_chk.find(".mp4") != std::string::npos || filename_chk.find(".mkv") != std::string::npos) {
            cur_filename = filename.toStdString();
            toolbox_window->setOutputDirectory(outdir, prefix);
            if(display_window->resetInputMode(InputMode::VIDEO,filename.toStdString())) {
                display_window->setPrefix(outdir, prefix);
                display_window->show();
                toolbox_window->setHide();
                fps = display_window->videoFPS(); // override new fps with video src
                display_window->startAnimation(fps);
                QString text;
                QTextStream stream(&text);
                stream << "gui: " << " opened: " << filename << " @ " << fps << " FPS / mode: VIDEO\n";
                debug_window->Log(text);
                filter_list->setEnabled(true);
                filter_list_view->setEnabled(true);
                filter_search->setEnabled(true);
                filter_search_button->setEnabled(true);
                filter_search_set->setEnabled(true);
                filter_cat->setEnabled(true);
                filter_first_set->setEnabled(true);
                filter_first_clear->setEnabled(true);
                edit_undo->setEnabled(true);
                edit_redo->setEnabled(true);
                display_window->clear_undo();
                toolbox_window->enableButtons();
                toolbox_window->disableSource();
                display_window->resetFrameCount();
                image_save->setEnabled(true);
                image_step->setEnabled(true);
                image_set_source->setEnabled(true);
                image_ani->setEnabled(true);
                return;
            }
        }
        cv::Mat src = cv::imread(filename.toStdString());
        if(!src.empty()) {
            cur_filename = filename.toStdString();
            toolbox_window->setOutputDirectory(outdir, prefix);
            display_window->setInputMode(InputMode::IMAGE);
            display_window->setGeometry(700, 100, 800, 600);
            display_window->setSourceImage(src);
            display_window->setPrefix(outdir, prefix);
            display_window->show();
            toolbox_window->setHide();

            if(record_window->rec_info.load_start == true)
                record();

            display_window->startAnimation(fps);
            QString text;
            QTextStream stream(&text);
            stream << "gui: " << " opened: " << filename << " @ " << fps << " FPS / mode: IMAGE\n";
            debug_window->Log(text);
            filter_list->setEnabled(true);
            filter_list_view->setEnabled(true);
            filter_search->setEnabled(true);
            filter_search_button->setEnabled(true);
            filter_search_set->setEnabled(true);
            filter_cat->setEnabled(true);
            filter_first_set->setEnabled(true);
            filter_first_clear->setEnabled(true);
            edit_undo->setEnabled(true);
            edit_redo->setEnabled(true);
            display_window->clear_undo();
            toolbox_window->enableButtons();
            toolbox_window->enableSource();
            display_window->resetFrameCount();
            image_save->setEnabled(true);
            image_step->setEnabled(true);
            image_set_source->setEnabled(true); 
            image_ani->setEnabled(true);
        } else {
            QMessageBox box;
            box.setWindowTitle("Error could not load image");
            box.setIcon(QMessageBox::Icon::Warning);
            box.setText("Could not load image");
            box.exec();
            display_window->clear_undo();
        }
    }
}


void MainWindow::openFile() {
    newimage_window->show();
}

void MainWindow::indexChanged(int) {
    std::string s = filter_list->currentText().toStdString();
    display_window->setCurrentFilter(s);
}

void MainWindow::catIndexChanged(int) {
    int index = filter_cat->currentIndex();
    loadCategory(index);
}

void MainWindow::searchFilter() {
    QString search = filter_search->text();
    if(search == "") return;
    filter_list_view->clear();
    for(int i = 0; i < filter_list->count(); ++i) {
        QString text = filter_list->itemText(i);
        if(text.contains(search)) {
            if(text.toStdString().find("InOrder") == std::string::npos)
                filter_list_view->addItem(text);
        }
    }
    filter_list_view->setCurrentRow(0);
    
}

void MainWindow::setSearch() {

    if(filter_list_view->count() == 0) 
        return;

    auto text = filter_list_view->currentItem();
    QString text_value = text->text();
    for(int i = 0; i < filter_list->count(); ++i) {
        QString compare = filter_list->itemText(i);
        if(compare == text_value) {
            filter_list->setCurrentIndex(i);
            break;
        }
    }
}

void MainWindow::helpAbout() {
    QString text;
    QTextStream stream(&text);
    stream << "Version: " << APP_VERSION << "\n" << "(C) 2023 LostSideDead Software\nProgrammed by " << AUTHOR_NAME << ".\n https://lostsidedead.biz\nThis software is dedicated to everyone who experiences mental illness.\n";
    QMessageBox box;
    box.setWindowTitle(tr(APP_NAME));
    box.setText(text);
    box.setWindowIcon(QIcon(":/images/icon.png"));
    box.setIcon(QMessageBox::Icon::Information);
    box.exec();
}

void MainWindow::firstSet() {
    QString text;
    QString fname = filter_list->currentText();
    QTextStream stream(&text);
    stream << "First: " << fname;
    filter_first->setText(text);
    first_filter = fname.toStdString();
    display_window->setFilterFirst(first_filter);
}

void MainWindow::firstClear() {
    filter_first->setText("First: None");
    first_filter = "None";
    display_window->setFilterFirst(first_filter);
}

void MainWindow::paintEvent(QPaintEvent *) {
    
}

// keypress event
void MainWindow::keyPressEvent(QKeyEvent *e)  {
    if(filter_list->isEnabled()) {
        switch(e->key()) {
            case Qt::Key_Up: {
                int pos = filter_list->currentIndex();
                if(pos-1 >= 0) {
                    filter_list->setCurrentIndex(pos-1);
                }
            }
                break;
            case Qt::Key_Down: {
                int pos = filter_list->currentIndex();
                if(pos + 1 < filter_list->count()) {
                    filter_list->setCurrentIndex(pos+1);
                }
            }
                break;
        }
    }
    
}

void MainWindow::keyShiftUp() {
    if(filter_list->isEnabled()) {
        int pos = filter_list->currentIndex();
        if(pos-1 >= 0) {
            filter_list->setCurrentIndex(pos-1);
        }
    }
}

void MainWindow::keyShiftDown() {
    if(filter_list->isEnabled()) {
        int pos = filter_list->currentIndex();
        if(pos + 1 < filter_list->count()) {
            filter_list->setCurrentIndex(pos+1);
        }
    }
}

void MainWindow::editUndo() {
    display_window->undo();
}
void MainWindow::editRedo() {
    display_window->redo();
}

void MainWindow::disableUndo() {
    edit_undo->setEnabled(false);
    edit_redo->setEnabled(false);
}

void MainWindow::enableUndo() {
    edit_undo->setEnabled(true);
    edit_redo->setEnabled(true);
}

void MainWindow::toggle_repeat() {
    if(record_repeat->isChecked()) {
        display_window->setRepeat(true);
        debug_window->Log("gui: Repeat toggled on\n");
    } else {
        display_window->setRepeat(false);
        debug_window->Log("gui: Repeat toggled off\n");
    }
}

void MainWindow::image_Save() {
    toolbox_window->saveSnapshot();
}

void MainWindow::image_Step() {
    toolbox_window->stepAction();
}

void MainWindow::image_Set() {
    toolbox_window->setSource();
}

void MainWindow::image_Ani() {
    toolbox_window->stopAction();
}

void MainWindow::setAniString(const QString &ani) {
    image_ani->setText(ani);
}

void MainWindow::filter_Show() {
    custom_window->show();
}

void MainWindow::filter_Edit() {
    
}