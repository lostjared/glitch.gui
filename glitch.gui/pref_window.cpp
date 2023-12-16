#include"pref_window.hpp"

PrefWindow::PrefWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(640, 480);
    setWindowTitle("Preferences");
}

void PrefWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}