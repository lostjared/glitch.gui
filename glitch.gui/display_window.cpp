#include"display_window.hpp"
#include"main_window.hpp"
#include<QPainter>

DisplayWindow::DisplayWindow(QWidget *parent) : QDialog(parent) {
    setGeometry(0, 0, 640, 480);
    setWindowTitle("Display Window");
    image_label = new QLabel(this);
    image_label->setGeometry(0, 0, 640, 480);

}

void DisplayWindow::setSourceImage(const cv::Mat &src) {
    source_image = src.clone();
    display(source_image);
}

void DisplayWindow::paintEvent(QPaintEvent *) {
    if(!source_image.empty()) {
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
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutFunc()));
    timer->start(1000 / 60);
}

void DisplayWindow::stopAnimation() {
    timer->stop();
}

void DisplayWindow::timeoutFunc() {
    display(source_image);
    update();
}
