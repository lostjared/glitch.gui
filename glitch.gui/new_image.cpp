#include"new_image.hpp"
#include"main_window.hpp"

NewImageWindow::NewImageWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Start new Animation");
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
    QLabel *cap = new QLabel(tr("FPS"), this);
    cap->setGeometry(10, 75, 50, 25);
    video_fps = new QLineEdit("24", this);
    video_fps->setGeometry(65, 75, 100, 25);
    video_start = new QPushButton(tr("Start"), this);
    video_start->setGeometry(320-100-10, 240-35, 100, 30);   
    connect(video_start, SIGNAL(clicked()), this, SLOT(videoStart())); 
    video_start->setEnabled(false);
}

void NewImageWindow::setMainWindow(MainWindow *main_w) {
    main_window = main_w;
}

void NewImageWindow::openFile() {

}

void NewImageWindow::selectDir() {

}

void NewImageWindow::videoStart() {
    float fps = video_fps->text().toFloat();
    if(fps > 0) {
        QString filename = input_file->text();
        QString outdir = output_location->text();
        main_window->startNewAnimation(filename, outdir, fps);
    }
}