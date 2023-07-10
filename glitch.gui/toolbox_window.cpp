#include"toolbox_window.hpp"

ToolboxWindow::ToolboxWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Toolbox");
}

void ToolboxWindow::setOutputDirectory(const QString &odir) {
    outdir = odir;
}
