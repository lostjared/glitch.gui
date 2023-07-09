#ifndef _DISP_WINDOW_H_
#define _DISP_WINDOW_H_

#include<QDialog>
#include<QPaintEvent>

#include"acidcam/ac.h"

class DisplayWindow : public QDialog {
    Q_OBJECT
public:
    DisplayWindow(QWidget *parent = 0);
    
    void setSourceImage(const cv::Mat &src);
    void paintEvent(QPaintEvent *e);

    void display(QImage &image);


private:
    cv::Mat source_image;
    
};




#endif