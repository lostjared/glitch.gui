#include"control_window.hpp"
#include"main_window.hpp"
#include"display_window.hpp"
#include<QTextStream>
#include<iostream>
#include<QVBoxLayout>
#include<QHBoxLayout>

Control_Window::Control_Window(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Video Controls");
    setWindowIcon(QIcon(":/images/icon.png"));
    setMinimumSize(500, 80);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(10);
    
    QHBoxLayout *ctrlRow = new QHBoxLayout();
    ctrlRow->setSpacing(10);
    
    ctrl_pos = new QScrollBar(Qt::Horizontal, this);
    ctrl_pos->setToolTip(tr("Duration within Video scrollbar"));
    ctrl_pos->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ctrl_pos->setEnabled(false);
    connect(ctrl_pos, SIGNAL(valueChanged(int)), this, SLOT(changedIndex(int)));
    
    ctrl_txt = new QLabel("0/0", this);
    ctrl_txt->setMinimumWidth(80);
    
    ctrl_set = new QPushButton(tr("Set Pos"), this);
    ctrl_set->setToolTip(tr("Set location within video"));
    ctrl_set->setMinimumWidth(80);
    ctrl_set->setEnabled(false);
    connect(ctrl_set, SIGNAL(clicked()), this, SLOT(setIndex()));
    
    ctrlRow->addWidget(ctrl_pos);
    ctrlRow->addWidget(ctrl_txt);
    ctrlRow->addWidget(ctrl_set);
    mainLayout->addLayout(ctrlRow);
    
    setLayout(mainLayout);
}


void Control_Window::setMainWindow(MainWindow *m) {
    main_window = m;
}

void Control_Window::enableControl(int min, int max) {
    ctrl_pos->setEnabled(true);
    ctrl_pos->setMinimum(min);
    ctrl_pos->setMaximum(max);
    ctrl_pos->setSliderPosition(0);
}

void Control_Window::setPos(int pos) {
    ctrl_pos->setSliderPosition(pos);
    setPosText(pos);
}

void Control_Window::setPosText(int pos) {
    QString text;
    QTextStream stream(&text);
    stream << pos << "/" << ctrl_pos->maximum();
    ctrl_txt->setText(text);
}

void Control_Window::changedIndex(int val) {
    setPosText(val);
}

void Control_Window::setIndex() {
    main_window->display_window->setVideoIndex(ctrl_pos->sliderPosition());
}