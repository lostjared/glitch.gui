#include"custom_window.hpp"
#include"main_window.hpp"

CustomWindow::CustomWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(640, 480);
    filter_cat = new QComboBox(this);
    filter_cat->setGeometry(15, 15, (640-15-15), 25);
    filter = new QComboBox(this);
    filter->setGeometry(15, 15+25+5, (640-15-10), 25);
    
}

void CustomWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}