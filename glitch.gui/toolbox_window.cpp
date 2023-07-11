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
    display_window->setSource();    
}