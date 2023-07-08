#include"display_window.hpp"

DisplayWindow::DisplayWindow(QWidget *parent) : QDialog(parent) {

    setFixedSize(640, 480);
    setWindowTitle("Display Window");
}

void DisplayWindow::display(QImage &/*image*/) {


}
