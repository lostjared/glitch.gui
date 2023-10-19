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
    
    debug_window = new DebugWindow(this);
    debug_window->show();
    
    toolbox_window = new ToolboxWindow(this);
    toolbox_window->setGeometry(100,100,250,400);
    toolbox_window->show();
    
    display_window = new DisplayWindow(this);
    display_window->setMainWindow(this);
    display_window->setGeometry(700, 600, 640, 480);
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

    setFixedSize(640, 360);
    setWindowTitle(tr(APP_NAME));
    file_menu = menuBar()->addMenu(tr("&File"));
    file_open = new QAction(tr("&Create New Image"), this);
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
    
    connect(filter_cat, SIGNAL(currentIndexChanged(int)), this, SLOT(catIndexChanged(int)));
    
    filter_list = new QComboBox(this);
    filter_list->setGeometry(15, 35+35, 300, 25);
    connect(filter_list, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));
    filter_list->setEnabled(false);
    
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
    
    filter_list_view->setEnabled(false);
    filter_search->setEnabled(false);
    filter_search_button->setEnabled(false);
    filter_search_set->setEnabled(false);
    filter_cat->setEnabled(false);
    filter_first_set->setEnabled(false);
    filter_first_clear->setEnabled(false);
    
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
}

void MainWindow::loadCategory(int index) {
    filter_list->clear();
    if(index == 5) {
        auto *a = &new_filter_list;
        for(int i = 0; i < static_cast<int>(a->size()); ++i) {
            filter_list->addItem(a->at(i).name);
        }
    } else {
        std::vector<std::string> *v = vec_cat[index];
        for(int i = 0; i < static_cast<int>(v->size()); ++i) {
            filter_list->addItem(v->at(i).c_str());
        }
    }
    filter_list_view->clear();
    filter_list->setCurrentIndex(0);
}

QString MainWindow::contentData(const std::string &fn, const cv::Mat &frame) {
    QString text;
    QTextStream stream(&text);
    stream << "path [" << fn.c_str() << "]" << "\n info [" << frame.cols << "x" << frame.rows << " channels: " << frame.channels() << "]\n";
    return text;
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
                return;
            }
        }
        cv::Mat src = cv::imread(filename.toStdString());
        if(!src.empty()) {
            cur_filename = filename.toStdString();
            toolbox_window->setOutputDirectory(outdir, prefix);
            display_window->setInputMode(InputMode::IMAGE);
            display_window->setGeometry(700, 100, 640, 480);
            display_window->setSourceImage(src);
            display_window->setPrefix(outdir, prefix);
            display_window->show();
            toolbox_window->setHide();
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
    stream << "Version: " << APP_VERSION << "\n" << "(C) 2023 LostSideDead Software\nProgrammed by " << AUTHOR_NAME << ".\n https://lostsidedead.biz\n";
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

