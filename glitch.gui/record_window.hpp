#ifndef RECORD_WINDOW_HPP_
#define RECORD_WINDOW_HPP_

#include<QDialog>

class MainWindow;

class RecordWindow : public QDialog {
    Q_OBJECT
public:
    RecordWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
private:
    MainWindow *main_window;
};


#endif