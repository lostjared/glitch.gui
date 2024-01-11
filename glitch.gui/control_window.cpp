#include"control_window.hpp"
#include<QTextStream>

Control_Window::Control_Window(QWidget *parent) : QDialog(parent) {
    setFixedSize(800, 100);
    ctrl_pos = new QScrollBar(Qt::Horizontal, this);
    ctrl_pos->setGeometry(25, 25, 400, 25);
    ctrl_pos->setEnabled(false);
        
    ctrl_txt = new QLabel("0/0", this);
    ctrl_txt->setGeometry(445, 25, 100, 25);
}


void Control_Window::setMainWindow(MainWindow *m) {
    main_window = m;
}

void Control_Window::enableControl(int min, int max) {
    ctrl_pos->setEnabled(true);
    ctrl_pos->setMinimum(min);
    ctrl_pos->setMaximum(max);
    ctrl_pos->setSliderPosition(0);
}

void Control_Window::setPos(int pos) {
    ctrl_pos->setSliderPosition(pos);
    QString text;
    QTextStream stream(&text);
    stream << pos << "/" << ctrl_pos->maximum();
    ctrl_txt->setText(text);
}
