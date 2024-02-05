#include"rotate_window.hpp"
#include"version_info.hpp"
#include<QIcon>
#include<QDialog>
#include<QFileDialog>
#include"ffmpeg_write.h"
#include<QMessageBox>

RotateWindow::RotateWindow(QWidget *parent) : QDialog(parent) {
    setGeometry(400, 100, 315, 135);
    setFixedSize(315, 135);
    setWindowTitle(tr("Rotate Video"));
    setWindowIcon(QIcon(":/images/icon.png"));

    item_src = new QLabel(tr("File to Rotate"), this);
    item_src->setGeometry(10,10,200, 25);
    src_select = new QPushButton(tr("Select"), this);
    src_select->setGeometry(10+200+10, 10, 75, 25);

    item_out = new QLabel(tr("File Output"), this);
    item_out->setGeometry(10,45,200,25);

    item_select = new QPushButton(tr("Select"), this);
    item_select->setGeometry(10+200+10, 45, 75, 25);

    btn_rotate = new QPushButton(tr("Rotate"), this);
    btn_rotate->setGeometry(10+200+10, 100, 75, 25);

    connect(src_select, SIGNAL(clicked()), this, SLOT(selectSrc()));
    connect(item_select, SIGNAL(clicked()), this, SLOT(selectDst()));
    connect(btn_rotate, SIGNAL(clicked()), this, SLOT(rotateVideo()));

    deg_rotate = new QComboBox(this);
    deg_rotate->setGeometry(10, 100, 100, 25);

    deg_rotate->addItem("90");
    deg_rotate->addItem("-90");
    deg_rotate->addItem("180");
    deg_rotate->setCurrentIndex(0);
}

void RotateWindow::selectSrc() {
    QString path="";
    QString filename = QFileDialog::getOpenFileName(this,tr("Open Image/Video"), path, tr("Image/Video Files (*.mov *.mp4 *.mkv)"));
    if(filename != "") {
        item_src->setText(filename);
        value_set[0] = true;
    }
}
 
void RotateWindow::selectDst() {
    QString path ="";
    QString filename = QFileDialog::getSaveFileName(this,tr("Open Image/Video"), path, tr("Image/Video Files (*.mp4 *.mov *.mkv)"));
    if(filename != "") {
        item_out->setText(filename);
        value_set[1] = true;
    }
}
 
void RotateWindow::rotateVideo() {
    if(value_set[0] && value_set[1]) {
        QMessageBox box;
        box.setWindowTitle(tr(APP_NAME));
        box.setText("This may take some time and program might lock up, watch the progress in the terminal window...");
        box.setWindowIcon(QIcon(":/images/icon.png"));
        box.setIcon(QMessageBox::Icon::Information);
        box.exec(); 
        rotate_90(item_src->text().toStdString().c_str(), item_out->text().toStdString().c_str(), deg_rotate->currentText().toStdString().c_str());
        box.setWindowTitle(tr(APP_NAME));
        box.setText("Rotate Video Completed...");
        box.setWindowIcon(QIcon(":/images/icon.png"));
        box.setIcon(QMessageBox::Icon::Information);
        box.exec(); 
    } else {
        QMessageBox box;
        box.setWindowTitle(tr(APP_NAME));
        box.setText("Please fill out the form, source video and output location");
        box.setWindowIcon(QIcon(":/images/icon.png"));
        box.setIcon(QMessageBox::Icon::Critical);
        box.exec(); 
    }
}
