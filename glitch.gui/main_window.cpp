#include "main_window.hpp"
#include<QMenuBar>
#include<QFileDialog>
#include<QPainter>
#include"toolbox_window.hpp"
#include"display_window.hpp"
#include"new_image.hpp"

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
    toolbox_window = new ToolboxWindow(this);
    toolbox_window->setGeometry(100,100,250,400);
    toolbox_window->show();

    display_window = new DisplayWindow(this);
    display_window->setGeometry(100, 600, 640, 480);
    display_window->hide();    

    newimage_window = new NewImageWindow(this);
    newimage_window->setGeometry(100, 100, 320, 240);
    newimage_window->setMainWindow(this);
    newimage_window->hide();

    setFixedSize(640, 480);
    setWindowTitle("glitch.gui");
    file_menu = menuBar()->addMenu("&File");
    file_open = new QAction(tr("&Create New Image"), this);
    connect(file_open, SIGNAL(triggered()), this, SLOT(openFile()));
    file_menu->addAction(file_open);

    setGeometry(375,100,640,480);

    filter_list = new QComboBox(this);
    filter_list->setGeometry(15, 15, 300, 25);
    for(auto it = ac::solo_filter.begin(); it != ac::solo_filter.end(); it++) {
        std::string s = *it;
        filter_list->addItem(s.c_str());
    }
    filter_list->setCurrentIndex(0);
    display_window->setCurrentFilter(ac::solo_filter[0]);

    connect(filter_list, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));
}


void MainWindow::startNewAnimation(const QString &filename, const QString &outdir, float fps) {
       if(filename != "") {
        cv::Mat src = cv::imread(filename.toStdString());
        if(!src.empty()) {
            display_window->setGeometry(0, 0, 800, 600);
            display_window->setSourceImage(src);
            display_window->show();
            display_window->startAnimation(fps);
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
    std::string s = ac::solo_filter[filter_list->currentIndex()];
    display_window->setCurrentFilter(s);
}


void MainWindow::paintEvent(QPaintEvent *) {

}
