#include "main_window.hpp"
#include<QMenuBar>
#include<QFileDialog>
#include<QPainter>
#include"toolbox_window.hpp"
#include"display_window.hpp"
#include"acidcam/ac.h"

MainWindow::MainWindow()  {

    ac::init();
    toolbox_window = new ToolboxWindow(this);
    toolbox_window->setGeometry(100,100,250,400);
    toolbox_window->show();

    display_window = new DisplayWindow(this);
    display_window->setGeometry(100, 600, 640, 480);
    display_window->hide();    

    setFixedSize(640, 480);
    setWindowTitle("glitch.gui");
    file_menu = menuBar()->addMenu("&File");
    file_open = new QAction(tr("&Open"), this);
    connect(file_open, SIGNAL(triggered()), this, SLOT(openFile()));
    file_menu->addAction(file_open);

    setGeometry(375,100,640,480);
}

void MainWindow::openFile() {
    QString filename;
    filename = QFileDialog::getOpenFileName(this,tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if(filename != "") {
        image = QImage(filename);
    }
}

void MainWindow::paintEvent(QPaintEvent *) {
    if(image.width() > 0) {
        /*
        QPainter paint(this);
        QImage scaled = image.scaled(QSize(640, 480), Qt::KeepAspectRatio);
        paint.drawImage(0, 0, scaled);*/
    }
}
