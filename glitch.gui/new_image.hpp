#ifndef _NEW_IMAGE_H_
#define _NEW_IMAGE_H_

#include<QDialog>

class MainWindow;

class NewImageWindow : public QDialog {
    Q_OBJECT
public:
    NewImageWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *main_w);
private:
    MainWindow *main_window;

};

#endif