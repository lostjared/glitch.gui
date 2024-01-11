#ifndef _CONTROL_WINDOW_H_
#define _CONTROL_WINDOW_H_

#include<QDialog>

class MainWindow;

class Control_Window : public QDialog {
Q_OBJECT

public:
    Control_Window(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);

private:
    MainWindow *main_window;


};


#endif