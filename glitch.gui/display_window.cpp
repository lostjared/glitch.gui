#include"display_window.hpp"
#include"main_window.hpp"
#include<QPainter>

DisplayWindow::DisplayWindow(QWidget *parent) : QDialog(parent) {

    setFixedSize(640, 480);
    setWindowTitle("Display Window");
}

void DisplayWindow::setSourceImage(const cv::Mat &src) {
    source_image = src.clone();
}

void DisplayWindow::paintEvent(QPaintEvent *) {
    if(!source_image.empty()) {
        QPainter paint(this);
        QImage image = Mat2QImage(source_image);
        paint.drawImage(0, 0, image);   
    }
}


void DisplayWindow::display(QImage &/*image*/) {

}
