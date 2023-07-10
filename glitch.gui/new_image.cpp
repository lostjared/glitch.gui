#include"new_image.hpp"
#include"main_window.hpp"

NewImageWindow::NewImageWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(320, 240);
    input_file = new QLabel(tr("Select File Location"), this);
    input_file->setGeometry(10, 10, 250, 25);
    input_file_select = new QPushButton("...", this);
    input_file_select->setGeometry(260, 10, 50, 25);
    connect(input_file_select, SIGNAL(clicked()), this, SLOT(openFile()));
    output_location = new QLabel(tr("Select Output Location"), this);
    output_location->setGeometry(10, 35, 250, 25);
    output_location_select = new QPushButton("...", this);
    output_location_select->setGeometry(260, 35, 50, 25);
    connect(output_location_select, SIGNAL(clicked()), this, SLOT(selectDir()));


}

void NewImageWindow::setMainWindow(MainWindow *main_w) {
    main_window = main_w;
}

void NewImageWindow::openFile() {

}

void NewImageWindow::selectDir() {

}