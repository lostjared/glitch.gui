#include"custom_window.hpp"
#include"main_window.hpp"

CustomWindow::CustomWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(640, 480);
}

void CustomWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}