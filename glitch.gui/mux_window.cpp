#include"mux_window.hpp"
#include<QIcon>


MuxWindow::MuxWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(640, 480);
    setWindowIcon(QIcon(":/images/icon.png"));
    setWindowTitle("Copy Audio");
    
}