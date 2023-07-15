#ifndef _DISP_WINDOW_H_
#define _DISP_WINDOW_H_

#include<QDialog>
#include<QPaintEvent>
#include<QLabel>
#include<QTimer>

#include"acidcam/ac.h"

class DebugWindow;

class DisplayWindow : public QDialog {
    Q_OBJECT
public:
    DisplayWindow(QWidget *parent = 0);

    void setDebugWindow(DebugWindow *d);    
    void setSourceImage(const cv::Mat &src);
    void paintEvent(QPaintEvent *e);

    void display(QImage &image);
    void display(const cv::Mat &src);

    void startAnimation();
    void startAnimation(float fps);
    void stopAnimation();
    void setCurrentFilter(const std::string &f);

    void takeSnapshot(const QString &text, const QString &file_type);
    void setSource();

    void step();

    void setColorOffset(const cv::Vec3b &color);

public slots:
    void timeoutFunc();


private:
    cv::Mat source_image, image;
    QLabel *image_label;
    QTimer *timer; 
    std::string current_filter;
    DebugWindow *debug_window;
    float fps = 24.0;
    cv::Vec3b color_offset;

    void setColorOffset(cv::Mat &frame);
};

#endif