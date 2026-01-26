#include"rotate_window.hpp"
#include"version_info.hpp"
#include<QIcon>
#include<QDialog>
#include<QFileDialog>
#include"ffmpeg_write.h"
#include<QMessageBox>
#include<QVBoxLayout>
#include<QHBoxLayout>

RotateWindow::RotateWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle(tr("Rotate Video"));
    setWindowIcon(QIcon(":/images/icon.png"));
    setMinimumSize(350, 150);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(10);
    
    QHBoxLayout *srcRow = new QHBoxLayout();
    srcRow->setSpacing(8);
    item_src = new QLabel(tr("File to Rotate"), this);
    item_src->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    src_select = new QPushButton(tr("Select"), this);
    src_select->setMinimumWidth(75);
    connect(src_select, SIGNAL(clicked()), this, SLOT(selectSrc()));
    srcRow->addWidget(item_src);
    srcRow->addWidget(src_select);
    mainLayout->addLayout(srcRow);
    
    QHBoxLayout *outRow = new QHBoxLayout();
    outRow->setSpacing(8);
    item_out = new QLabel(tr("File Output"), this);
    item_out->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    item_select = new QPushButton(tr("Select"), this);
    item_select->setMinimumWidth(75);
    connect(item_select, SIGNAL(clicked()), this, SLOT(selectDst()));
    outRow->addWidget(item_out);
    outRow->addWidget(item_select);
    mainLayout->addLayout(outRow);
    
    mainLayout->addStretch();
    
    QHBoxLayout *rotateRow = new QHBoxLayout();
    rotateRow->setSpacing(8);
    deg_rotate = new QComboBox(this);
    deg_rotate->setMinimumWidth(100);
    deg_rotate->addItem("90");
    deg_rotate->addItem("-90");
    deg_rotate->addItem("180");
    deg_rotate->setCurrentIndex(0);
    btn_rotate = new QPushButton(tr("Rotate"), this);
    btn_rotate->setMinimumWidth(75);
    connect(btn_rotate, SIGNAL(clicked()), this, SLOT(rotateVideo()));
    rotateRow->addWidget(deg_rotate);
    rotateRow->addStretch();
    rotateRow->addWidget(btn_rotate);
    mainLayout->addLayout(rotateRow);
    
    setLayout(mainLayout);
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
