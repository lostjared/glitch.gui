#include"mux_window.hpp"
#include<QIcon>
#include<QFileDialog>
#include"ffmpeg_write.h"
#include<QMessageBox>
#include"version_info.hpp"
#include<QVBoxLayout>
#include<QHBoxLayout>

MuxWindow::MuxWindow(QWidget *parent) : QDialog(parent) {
    setWindowIcon(QIcon(":/images/icon.png"));
    setWindowTitle("Copy Audio");
    setMinimumSize(450, 180);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(10);
    
    QHBoxLayout *srcRow = new QHBoxLayout();
    srcRow->setSpacing(8);
    file_source = new QLabel("[ Source File ]", this);
    file_source->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    select_source = new QPushButton(tr("Select File"), this);
    select_source->setMinimumWidth(100);
    connect(select_source, SIGNAL(clicked()), this, SLOT(select_Source()));
    srcRow->addWidget(file_source);
    srcRow->addWidget(select_source);
    mainLayout->addLayout(srcRow);
    
    QHBoxLayout *copyRow = new QHBoxLayout();
    copyRow->setSpacing(8);
    file_copy = new QLabel("[ Audio to Copy ]", this);
    file_copy->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    select_copy = new QPushButton(tr("Select File"), this);
    select_copy->setMinimumWidth(100);
    connect(select_copy, SIGNAL(clicked()), this, SLOT(select_Copy()));
    copyRow->addWidget(file_copy);
    copyRow->addWidget(select_copy);
    mainLayout->addLayout(copyRow);
    
    QHBoxLayout *destRow = new QHBoxLayout();
    destRow->setSpacing(8);
    file_dest = new QLabel("[ Destination File ]", this);
    file_dest->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    select_dest = new QPushButton(tr("Select File"), this);
    select_dest->setMinimumWidth(100);
    connect(select_dest, SIGNAL(clicked()), this, SLOT(select_Dest()));
    destRow->addWidget(file_dest);
    destRow->addWidget(select_dest);
    mainLayout->addLayout(destRow);
    
    mainLayout->addStretch();
    
    QHBoxLayout *btnRow = new QHBoxLayout();
    btnRow->addStretch();
    mux_files = new QPushButton(tr("Mux Files"), this);
    mux_files->setMinimumWidth(100);
    connect(mux_files, SIGNAL(clicked()), this, SLOT(mux_Files()));
    btnRow->addWidget(mux_files);
    mainLayout->addLayout(btnRow);
    
    setLayout(mainLayout);
}

void MuxWindow::select_Source() {
    QString path = "";
    QString filename = QFileDialog::getOpenFileName(this,tr("Open Image/Video"), path, tr("Image/Video Files (*.mov *.mp4 *.mkv)"));
    if(filename != "") {
        file_source->setText(filename);
        values_set[0] = true;
    }
}
void MuxWindow::select_Copy() {
    QString path = "";
    QString filename = QFileDialog::getOpenFileName(this,tr("Open Image/Video"), path, tr("Image/Video Files (*.mov *.mp4 *.mkv)"));
    if(filename != "") {
        file_copy->setText(filename);
        values_set[1] = true;
    }
}
void MuxWindow::select_Dest() {
    QString path = "";
    QString filename = QFileDialog::getSaveFileName(this,tr("Open Image/Video"), path, tr("Image/Video Files (*.mp4 *.mov *.mkv)"));
    if(filename != "") {
        file_dest->setText(filename);
        values_set[2] = true;
    }
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
