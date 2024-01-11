#include"toolbox_window.hpp"
#include"display_window.hpp"
#include"record_window.hpp"
#include"main_window.hpp"
#include"debug_window.hpp"
#include<QColorDialog>

ToolboxWindow::ToolboxWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Toolbox");
    setWindowFlags(Qt::WindowType::Tool);
    save_snapshot = new QPushButton(tr("Save"), this);
    save_snapshot->setGeometry(10, 10, 100, 25);
    connect(save_snapshot, SIGNAL(clicked()), this, SLOT(saveSnapshot()));
    
    setsource_action = new QPushButton(tr("Source"), this);
    setsource_action->setGeometry(120, 10, 100, 25);
    connect(setsource_action, SIGNAL(clicked()), this, SLOT(setSource()));
    
    stop_action = new QPushButton(tr("Stop"), this);
    stop_action->setGeometry(10, 40, 100, 25);
    connect(stop_action, SIGNAL(clicked()), this, SLOT(stopAction()));
    
    step_action = new QPushButton(tr("Step"), this);
    step_action->setGeometry(120, 40, 100, 25);
    connect(step_action, SIGNAL(clicked()), this, SLOT(stepAction()));
    
    color_lbl = new QLabel(this);
    color_lbl->setGeometry(10, 40+25+10, 75, 25);
    QString color_var = "#000000";
    color_lbl->setStyleSheet("QLabel { background-color :" + color_var + " ; }");
    use_color = new QCheckBox(tr("Offset Color"), this);
    use_color->setGeometry(120,40+25+10, 100, 25);
    use_color->setChecked(false);
    use_fade = new QCheckBox(tr("Fade"), this);
    use_fade->setGeometry(120,40+25+10+30, 100, 25);
    use_fade->setChecked(false);
    sel_color = new QPushButton("...", this);
    sel_color->setGeometry(10+75, 40+25+10, 25, 25);
    connect(sel_color, SIGNAL(clicked()), this, SLOT(selectColor()));
    connect(use_color, SIGNAL(toggled(bool)), this, SLOT(clickOffset(bool)));
    connect(use_fade, SIGNAL(toggled(bool)), this, SLOT(clickFade(bool)));

    show_disp = new QPushButton(tr("Show"), this);
    show_disp->setGeometry(10,45+25+10+25,100,25);
    connect(show_disp, SIGNAL(clicked()), this, SLOT(showDisplay()));

    record_btn = new QPushButton(tr("Rec Settings"), this);
    record_btn->setGeometry(10, 45+25+10+25+25+5,100,25);
    connect(record_btn, SIGNAL(clicked()), this, SLOT(showRecord()));

    record_now = new QPushButton(tr("Record"), this);
    record_now->setGeometry(120, 45+25+10+25+25+5, 100, 25);
    connect(record_now, SIGNAL(clicked()), this, SLOT(recordNow()));

    disableButtons();
    //setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
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
