#include"control_window.hpp"

Control_Window::Control_Window(QWidget *parent) : QDialog(parent) {


}


void Control_Window::setMainWindow(MainWindow *m) {
    main_window = m;
}
