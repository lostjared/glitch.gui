#include"display_window.hpp"
#include"main_window.hpp"
#include"debug_window.hpp"

#include<QPainter>

DisplayWindow::DisplayWindow(QWidget *parent) : QDialog(parent) {
    setGeometry(700, 0, 640, 480);
    setWindowTitle("Display Window");
    image_label = new QLabel(this);
    image_label->setGeometry(0, 0, 640, 480);
    // don't use debug_window not initalized yet
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutFunc()));
}

void DisplayWindow::setDebugWindow(DebugWindow *d) {
    debug_window = d;
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
    timer->start(static_cast<int>((double)1000 / this->fps));
}

void DisplayWindow::startAnimation(float fps) {
    this->fps = fps;
    timer->start(static_cast<int>((double)1000 / fps));
}

void DisplayWindow::stopAnimation() {
    timer->stop();
}

void DisplayWindow::setCurrentFilter(const std::string &f) {
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
    stream << filename << image.cols << "x" << image.rows << "." << file_type;
    cv::imwrite(text.toStdString(), image);
    QString textx;
    QTextStream streamx(&textx);
    streamx << "glitch: Took snapshot: " << text << "\n";
    debug_window->Log(textx);
}

void DisplayWindow::setSource() {
    source_image = image.clone();
    QString text;
    QTextStream stream(&text);
    stream << "glitch: Set current frame as Source image\n";
    debug_window->Log(text);
}

void DisplayWindow::step() {
    timeoutFunc();    
}

void DisplayWindow::timeoutFunc() {
    image = source_image.clone();
    ac::CallFilter(current_filter, image);
    display(image);
    update();
}
