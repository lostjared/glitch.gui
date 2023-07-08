#include "main_window.hpp"
#include<QMenuBar>
#include<QFileDialog>
#include<QPainter>
#include"toolbox_window.hpp"
#include"display_window.hpp"

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

    setFixedSize(640, 480);
    setWindowTitle("glitch.gui");
    file_menu = menuBar()->addMenu("&File");
    file_open = new QAction(tr("&Open"), this);
    connect(file_open, SIGNAL(triggered()), this, SLOT(openFile()));
    file_menu->addAction(file_open);

    setGeometry(375,100,640,480);
}

void MainWindow::openFile() {
    QString filename;
    filename = QFileDialog::getOpenFileName(this,tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if(filename != "") {
        if(image.load(filename)) {
            QImage scaled = image.scaled(QSize(640, 480), Qt::KeepAspectRatio);
            setFixedSize(scaled.width(), scaled.height());
        }
     }
}

void MainWindow::paintEvent(QPaintEvent *) {
    if(image.width() > 0) {        
        QPainter paint(this);
        QImage scaled = image.scaled(QSize(640, 480), Qt::KeepAspectRatio);     
        paint.drawImage(0, 0, scaled);
    }
}
