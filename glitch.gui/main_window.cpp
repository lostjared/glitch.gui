#include "main_window.hpp"
#include<QMenuBar>
#include"toolbox_window.hpp"

MainWindow::MainWindow()  {

    toolbox_window = new ToolboxWindow(this);
    toolbox_window->setGeometry(100,100,250,400);
    toolbox_window->show();

    setFixedSize(640, 480);
    setWindowTitle("glitch.gui");
    file_menu = menuBar()->addMenu("&File");
    file_open = new QAction(tr("&Open"), this);
    connect(file_open, SIGNAL(triggered()), this, SLOT(openFile()));
    file_menu->addAction(file_open);

    setGeometry(375,100,640,480);
}

void MainWindow::openFile() {

}
