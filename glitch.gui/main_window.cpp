#include "main_window.hpp"
#include<QMenuBar>
#include<QFileDialog>
#include<QPainter>
#include<QMessageBox>
#include"toolbox_window.hpp"
#include"display_window.hpp"
#include"new_image.hpp"
#include"debug_window.hpp"
#include"cat_vec.hpp"

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
    display_window->setGeometry(700, 600, 640, 480);
    display_window->hide();  
    display_window->setDebugWindow(debug_window);

    toolbox_window->setDisplayWindow(display_window);  

    newimage_window = new NewImageWindow(this);
    newimage_window->setGeometry(700, 100, 320, 240);
    newimage_window->setMainWindow(this);
    newimage_window->hide();

    setFixedSize(640, 480);
    setWindowTitle(tr("glitch.gui"));
    file_menu = menuBar()->addMenu(tr("&File"));
    file_open = new QAction(tr("&Create New Image"), this);
    connect(file_open, SIGNAL(triggered()), this, SLOT(openFile()));
    file_menu->addAction(file_open);

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

    connect(filter_cat, SIGNAL(currentIndexChanged(int)), this, SLOT(catIndexChanged(int)));
    
    filter_list = new QComboBox(this);
    filter_list->setGeometry(15, 35+35, 300, 25);
    connect(filter_list, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));
    filter_list->setEnabled(false);

    filter_list_view = new QListWidget(this);
    filter_list_view->setGeometry(15, 35+25+10+35, 300, 200);

    filter_search = new QLineEdit(this);
    filter_search->setGeometry(300+15+10, 35, 300-75, 30);

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

    loadCategory(0);
    setWindowIcon(QIcon(":/images/icon.png"));
    display_window->setFilterFirst("None");
    debug_window->Log("gui: successfully initalized\n");
}

void MainWindow::loadCategory(int index) {
    filter_list->clear();
    std::vector<std::string> *v = vec_cat[index];
    for(int i = 0; i < static_cast<int>(v->size()); ++i) {
        filter_list->addItem(v->at(i).c_str());
    }
    filter_list_view->clear();
    filter_list->setCurrentIndex(0);
}

void MainWindow::startNewAnimation(const QString &filename, const QString &outdir, const QString &prefix, float fps) {
       if(filename != "") {
        cv::Mat src = cv::imread(filename.toStdString());
        if(!src.empty()) {
            toolbox_window->setOutputDirectory(outdir, prefix);
            display_window->setGeometry(700, 0, 800, 600);
            display_window->setSourceImage(src);
            display_window->show();
            display_window->startAnimation(fps);
            QString text;
            QTextStream stream(&text);
            stream << "gui: " << " opened: " << filename << " @ " << fps << " FPS\n";
            debug_window->Log(text);
            filter_list->setEnabled(true);
            filter_list_view->setEnabled(true);
            filter_search->setEnabled(true);
            filter_search_button->setEnabled(true);
            filter_search_set->setEnabled(true);
            filter_cat->setEnabled(true);
            filter_first_set->setEnabled(true);
            filter_first_clear->setEnabled(true);
            toolbox_window->enableButtons();
        }
     } 
}


void MainWindow::openFile() {
    /*
    QString filename;
    filename = QFileDialog::getOpenFileName(this,tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if(filename != "") {
        cv::Mat src = cv::imread(filename.toStdString());
        if(!src.empty()) {
            display_window->setGeometry(0, 0, 800, 600);
            display_window->setSourceImage(src);
            display_window->show();
            display_window->startAnimation();
        }
     }*/
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
    stream << "Version: " << APP_VERSION << "\n" << "(C) 2023 LostSideDead Software\nProgrammed by Jared Bruni. https://lostsidedead.biz\n";
    QMessageBox box;
    box.setWindowTitle(tr("About glitch.gui"));
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
