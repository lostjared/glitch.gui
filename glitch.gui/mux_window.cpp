#include"mux_window.hpp"
#include<QIcon>
#include<QFileDialog>
#include"ffmpeg_write.h"
#include<QMessageBox>
#include"version_info.hpp"

MuxWindow::MuxWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(480, 200);
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

    mux_files = new QPushButton(tr("Mux Files"), this);
    mux_files->setGeometry(340, 60+25+5+25+5, 100, 25);

    connect(select_source, SIGNAL(clicked()), this, SLOT(select_Source()));
    connect(select_copy, SIGNAL(clicked()), this, SLOT(select_Copy()));
    connect(select_dest, SIGNAL(clicked()), this, SLOT(select_Dest()));
    connect(mux_files, SIGNAL(clicked()), this, SLOT(mux_Files()));
    
}

void MuxWindow::select_Source() {
    QString path = "";
    QString filename = QFileDialog::getOpenFileName(this,tr("Open Image/Video"), path, tr("Image/Video Files (*.mov *.mp4 *.mkv)"));
    file_source->setText(filename);
    values_set[0] = true;
}
void MuxWindow::select_Copy() {
    QString path = "";
    QString filename = QFileDialog::getOpenFileName(this,tr("Open Image/Video"), path, tr("Image/Video Files (*.mov *.mp4 *.mkv)"));
    file_copy->setText(filename);
    values_set[1] = true;
}
void MuxWindow::select_Dest() {
    QString path = "";
    QString filename = QFileDialog::getSaveFileName(this,tr("Open Image/Video"), path, tr("Image/Video Files (*.mp4 *.mov *.mkv)"));
    file_dest->setText(filename);
    values_set[2] = true;
}
void MuxWindow::mux_Files() {
    if(values_set[0] && values_set[1] && values_set[2]) {
        mux_audio(file_source->text().toStdString().c_str(), file_copy->text().toStdString().c_str(), file_dest->text().toStdString().c_str());
        QMessageBox box;
        box.setWindowTitle(tr("Succesfull"));
        box.setText("Muxed audio: " + file_dest->text());
        box.setWindowIcon(QIcon(":/images/icon.png"));
        box.setIcon(QMessageBox::Icon::Information);
        box.exec();
    } else {
        QMessageBox box;
        box.setWindowTitle(tr("Required Info Missing"));
        box.setText("Please select files and destination.");
        box.setWindowIcon(QIcon(":/images/icon.png"));
        box.setIcon(QMessageBox::Icon::Information);
        box.exec();
    }
}
