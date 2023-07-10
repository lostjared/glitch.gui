#include"new_image.hpp"
#include"main_window.hpp"

NewImageWindow::NewImageWindow(QWidget *parent) : QDialog(parent) {

}

void NewImageWindow::setMainWindow(MainWindow *main_w) {
    main_window = main_w;
}
