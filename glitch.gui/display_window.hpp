#ifndef _DISP_WINDOW_H_
#define _DISP_WINDOW_H_

#include<QDialog>


class DisplayWindow : public QDialog {
    Q_OBJECT
public:
    DisplayWindow(QWidget *parent = 0);
    
    void display(QImage &image);
    
};




#endif