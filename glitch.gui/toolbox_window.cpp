#include"toolbox_window.hpp"
#include"display_window.hpp"
#include"record_window.hpp"
#include"main_window.hpp"
#include"debug_window.hpp"
#include<QColorDialog>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>

ToolboxWindow::ToolboxWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Toolbox");
    setWindowFlags(Qt::WindowType::Tool);
    setWindowIcon(QIcon(":/images/icon.png"));
    setMinimumSize(250, 220);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(8);
    
    QHBoxLayout *row1 = new QHBoxLayout();
    row1->setSpacing(8);
    save_snapshot = new QPushButton(tr("Save"), this);
    save_snapshot->setToolTip(tr("Save Snapshot Image"));
    connect(save_snapshot, SIGNAL(clicked()), this, SLOT(saveSnapshot()));
    setsource_action = new QPushButton(tr("Source"), this);
    setsource_action->setToolTip(tr("Set current Image as Source image"));
    connect(setsource_action, SIGNAL(clicked()), this, SLOT(setSource()));
    row1->addWidget(save_snapshot);
    row1->addWidget(setsource_action);
    mainLayout->addLayout(row1);
    
    QHBoxLayout *row2 = new QHBoxLayout();
    row2->setSpacing(8);
    stop_action = new QPushButton(tr("Stop"), this);
    stop_action->setToolTip(tr("Stop Animation"));
    connect(stop_action, SIGNAL(clicked()), this, SLOT(stopAction()));
    step_action = new QPushButton(tr("Step"), this);
    step_action->setToolTip(tr("Step forward one frame"));
    connect(step_action, SIGNAL(clicked()), this, SLOT(stepAction()));
    row2->addWidget(stop_action);
    row2->addWidget(step_action);
    mainLayout->addLayout(row2);
    
    QHBoxLayout *row3 = new QHBoxLayout();
    row3->setSpacing(8);
    color_lbl = new QLabel(this);
    color_lbl->setFixedSize(50, 25);
    QString color_var = "#000000";
    color_lbl->setStyleSheet("QLabel { background-color :" + color_var + " ; }");
    sel_color = new QPushButton("...", this);
    sel_color->setFixedWidth(30);
    connect(sel_color, SIGNAL(clicked()), this, SLOT(selectColor()));
    use_color = new QCheckBox(tr("Offset Color"), this);
    use_color->setToolTip(tr("Offset color values"));
    use_color->setChecked(false);
    connect(use_color, SIGNAL(toggled(bool)), this, SLOT(clickOffset(bool)));
    row3->addWidget(color_lbl);
    row3->addWidget(sel_color);
    row3->addWidget(use_color);
    row3->addStretch();
    mainLayout->addLayout(row3);
    
    QHBoxLayout *row4 = new QHBoxLayout();
    row4->setSpacing(8);
    use_fade = new QCheckBox(tr("Fade"), this);
    use_fade->setToolTip(tr("Fade turn on?"));
    use_fade->setChecked(false);
    connect(use_fade, SIGNAL(toggled(bool)), this, SLOT(clickFade(bool)));
    show_disp = new QPushButton(tr("Show"), this);
    show_disp->setToolTip(tr("Show/Hide Display Window"));
    connect(show_disp, SIGNAL(clicked()), this, SLOT(showDisplay()));
    row4->addWidget(use_fade);
    row4->addWidget(show_disp);
    mainLayout->addLayout(row4);
    
    QHBoxLayout *row5 = new QHBoxLayout();
    row5->setSpacing(8);
    record_btn = new QPushButton(tr("Rec Settings"), this);
    record_btn->setToolTip(tr("Record Settings"));
    connect(record_btn, SIGNAL(clicked()), this, SLOT(showRecord()));
    record_now = new QPushButton(tr("Record"), this);
    record_now->setToolTip(tr("Record Button"));
    connect(record_now, SIGNAL(clicked()), this, SLOT(recordNow()));
    record_now->setEnabled(false);
    row5->addWidget(record_btn);
    row5->addWidget(record_now);
    mainLayout->addLayout(row5);
    
    mainLayout->addStretch();
    setLayout(mainLayout);
    
    disableButtons();
}

void ToolboxWindow::enableRecord() {
    record_now->setEnabled(true);
}

void ToolboxWindow::recordNow() {
    display_window->record();
    if(display_window->recording()) {
        record_now->setText(tr("Stop"));
    } else {
        record_now->setText(tr("Record"));
    }
}

void ToolboxWindow::setHide() {
    show_disp->setText("Hide");
}

void ToolboxWindow::setShow() {
    show_disp->setText("Show");
}

void ToolboxWindow::showDisplay() {
    if(show_disp->text() == "Show") {
        display_window->show();
        show_disp->setText("Hide");
    } else {
        display_window->hide();
        show_disp->setText("Show");
    }
}

void ToolboxWindow::setRecordText(bool b) {
    if(b) {
        record_now->setText(tr("Record"));
    } else {
        record_now->setText(tr("Stop"));
    }
}

void ToolboxWindow::showRecord() {
    if(record_window != nullptr) record_window->show();    
}

void ToolboxWindow::clickFade(bool) {
    if(use_fade->isChecked()) {
        display_window->setFade(true);
    } else {
        display_window->setFade(false);
    }
}

void ToolboxWindow::enableButtons() {
    sel_color->setEnabled(true);
    use_color->setEnabled(true);
    save_snapshot->setEnabled(true);
    setsource_action->setEnabled(true);
    stop_action->setEnabled(true);
    stop_action->setText(tr("Stop"));
    step_action->setEnabled(true);
}

void ToolboxWindow::disableButtons() {
    sel_color->setEnabled(false);
    use_color->setEnabled(false);
    save_snapshot->setEnabled(false);
    setsource_action->setEnabled(false);
    stop_action->setEnabled(false);
    step_action->setEnabled(false);
}


void ToolboxWindow::setOutputDirectory(const QString &odir, const QString &p) {
    outdir = odir;
    prefix = p;
}

void ToolboxWindow::setDisplayWindow(DisplayWindow *disp) {
    display_window = disp;
    display_window->setColorOffset(cv::Vec3b(0, 0, 0));
}

void ToolboxWindow::setRecordWindow(RecordWindow *r) {
    record_window = r;
}


void ToolboxWindow::saveSnapshot() {
    if(outdir != "") {
        QString text;
        QTextStream stream(&text);
        stream << outdir << "/" << prefix << "-" << ++snap_index << "-";
        display_window->takeSnapshot(text, "png");
    }
}

void ToolboxWindow::setSource() {
    if(display_window != nullptr)
        display_window->setSource();    
}

void ToolboxWindow::stopAction() {
    
    if(stop_action->text() == "Stop") {
        if(display_window != nullptr)
            display_window->stopAnimation();
        stop_action->setText("Start");
        main_window->setAniString(stop_action->text());
    } else {
        stop_action->setText("Stop");
        main_window->setAniString(stop_action->text());
        if(display_window != nullptr)
            display_window->startAnimation();
    }
}

void ToolboxWindow::stepAction() {
    if(display_window != nullptr) {
        display_window->step();
        if(main_window != nullptr)
            main_window->debug_window->Log("gui: Step forward taken.\n");
    }
    
}

void ToolboxWindow::selectColor() {
    QColorDialog *dialog = new QColorDialog(this);
    QColor color=  dialog->getColor();
    QVariant variant = color;
    QString color_var = variant.toString();
    //set_low_color = color;
    color_value[0] = color.blue();
    color_value[1] = color.green();
    color_value[2] = color.blue();
    color_lbl->setStyleSheet("QLabel { background-color :" + color_var + " ; }");
}

void ToolboxWindow::clickOffset(bool) {
    if(use_color->isChecked()) {
        display_window->setColorOffset(color_value);
    } else {
        display_window->setColorOffset(cv::Vec3b(0, 0, 0));
    }
}

void ToolboxWindow::enableSource() {
    setsource_action->setEnabled(true);
    
}

void ToolboxWindow::disableSource() {
    setsource_action->setEnabled(false);
}

void ToolboxWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}

void ToolboxWindow::setStopText() {
    stop_action->setText("Stop");
    main_window->setAniString("Stop");
}

void ToolboxWindow::setStartText() {
    stop_action->setText("Start");
    main_window->setAniString("Start");
}
