#ifndef _CONTROL_WINDOW_H_
#define _CONTROL_WINDOW_H_

#include<QDialog>
#include<QScrollBar>
#include<QLabel>
#include<QPushButton>

class MainWindow;

class Control_Window : public QDialog {
Q_OBJECT

public:
    Control_Window(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
    void enableControl(int min, int max);
    void setPos(int pos);
    void setPosText(int pos); 
    QScrollBar *ctrl_pos;
    QLabel *ctrl_txt;

private:
    MainWindow *main_window;
    QPushButton *ctrl_set;
public slots:
    void changedIndex(int val);
    void setIndex();

};


#endif