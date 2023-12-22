#include"mux_window.hpp"
#include<QIcon>


MuxWindow::MuxWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(640, 480);
    setWindowIcon(QIcon(":/images/icon.png"));
    setWindowTitle("Copy Audio");
    file_source = new QLabel("[ Source File ]", this);
    file_source->setGeometry(25, 25, 300, 25);
    file_copy = new QLabel("[ Audio to Copy ]", this);
    file_copy->setGeometry(25, 60, 300, 25);
    file_dest = new QLabel("[ Destination FIle ]", this);
    file_dest->setGeometry(25, 60+25+5, 300, 25);

    select_source = new QPushButton(tr("Select File"), this);
    select_source->setGeometry(340,25,100,25);
    select_copy = new QPushButton(tr("Select File"), this);
    select_copy->setGeometry(340, 60, 100, 25);
    select_dest = new QPushButton(tr("Select File"), this);
    select_dest->setGeometry(340, 60+25+5,100,25);

    
}