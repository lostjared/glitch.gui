#include"display_window.hpp"
#include"main_window.hpp"
#include"debug_window.hpp"

#include<QPainter>
#include<QIcon>
#include<QDateTime>
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
    image = source_image.clone();
    if(first_filter != "None")
        New_CallFilter(first_filter, image);

    New_CallFilter(current_filter, image);
    setColorOffset(image);
    display(image);
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