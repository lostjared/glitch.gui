#include"toolbox_window.hpp"
#include"display_window.hpp"

ToolboxWindow::ToolboxWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Toolbox");
    save_snapshot = new QPushButton(tr("Save"), this);
    save_snapshot->setGeometry(10, 10, 100, 25);
    connect(save_snapshot, SIGNAL(clicked()), this, SLOT(saveSnapshot()));

    setsource_action = new QPushButton(tr("Set"), this);
    setsource_action->setGeometry(120, 10, 100, 25);
    connect(setsource_action, SIGNAL(clicked()), this, SLOT(setSource()));

    stop_action = new QPushButton(tr("Stop"), this);
    stop_action->setGeometry(10, 40, 100, 25);
    connect(stop_action, SIGNAL(clicked()), this, SLOT(stopAction()));

    step_action = new QPushButton(tr("Step"), this);
    step_action->setGeometry(120, 40, 100, 25);
    connect(step_action, SIGNAL(clicked()), this, SLOT(stepAction()));

}

void ToolboxWindow::setOutputDirectory(const QString &odir) {
    outdir = odir;
}

void ToolboxWindow::setDisplayWindow(DisplayWindow *disp) {
    display_window = disp;
}

void ToolboxWindow::saveSnapshot() {
    if(outdir != "") {
        QString text;
        QTextStream stream(&text);
        stream << outdir << "/" << "glitch.gui.snapshot-" << ++snap_index << "-";
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
    } else {
        stop_action->setText("Stop");
        if(display_window != nullptr)
            display_window->startAnimation();
    }
}

void ToolboxWindow::stepAction() {
    if(display_window != nullptr) 
        display_window->step();

}