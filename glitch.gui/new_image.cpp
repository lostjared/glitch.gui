#include"new_image.hpp"
#include"main_window.hpp"
#include<QFileDialog>
#include<QIcon>

NewImageWindow::NewImageWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Start new Animation");
    setWindowIcon(QIcon(":/images/icon.png"));
    setFixedSize(320, 240);
    input_file = new QLabel(tr("Select File Location"), this);
    input_file->setGeometry(10, 10, 240, 25);
    input_file_select = new QPushButton("...", this);
    input_file_select->setGeometry(260, 10, 50, 25);
    connect(input_file_select, SIGNAL(clicked()), this, SLOT(openFile()));
    output_location = new QLabel(tr("Select Output Location"), this);
    output_location->setGeometry(10, 35, 240, 25);
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
    filename_set = false;
    outdir_set = false;
    QLabel *prefix = new QLabel(tr("Filename Prefix:"), this);
    prefix->setGeometry(10, 110, 100, 30);
    video_filename = new QLineEdit(this);
    video_filename->setText(tr("glitch.gui.file1"));
    video_filename->setGeometry(110, 110, 195, 30);
}

void NewImageWindow::setMainWindow(MainWindow *main_w) {
    main_window = main_w;
}

void NewImageWindow::openFile() {
    QString filename;
    filename = QFileDialog::getOpenFileName(this,tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if(filename != "") {
        input_file->setText(filename);
        filename_set = true;
        if(outdir_set == true && filename_set == true) {
            video_start->setEnabled(true);
        }
    }
}

void NewImageWindow::selectDir() {
    QString dir;
    dir = QFileDialog::getExistingDirectory(this, tr("Open Dir"), "");
    if(dir != "") {
        output_location->setText(dir);
        outdir_set = true;
        if(outdir_set == true && filename_set == true) {
            video_start->setEnabled(true);
        }
    }

}

void NewImageWindow::videoStart() {
    float fps = video_fps->text().toFloat();
    QString prefix = video_filename->text();

    if(fps > 0 && prefix.length() > 0 && filename_set == true && outdir_set == true) {
        QString filename = input_file->text();
        QString outdir = output_location->text();
        main_window->startNewAnimation(filename, outdir, prefix, fps);
        hide();
    }
}