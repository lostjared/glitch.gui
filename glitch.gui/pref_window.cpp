#include"pref_window.hpp"

PrefWindow::PrefWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(640, 480);
    setWindowTitle("Preferences");

    chk_path = new QCheckBox(tr("Save Directory Paths"), this);
    chk_path->setGeometry(25,25,200,25);
}

void PrefWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}