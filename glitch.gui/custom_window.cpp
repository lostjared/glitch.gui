#include"custom_window.hpp"
#include"main_window.hpp"

CustomWindow::CustomWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(640, 480);
    filter_cat = new QComboBox(this);
    filter_cat->setGeometry(15, 15, (640-15-15), 25);
    filter = new QComboBox(this);
    filter->setGeometry(15, 15+25+5, (640-15-15), 25);

    filter_custom = new QListWidget(this);
    filter_custom->setGeometry(15, 15+25+5+25+5, (640-15-15), 300);
    
}

void CustomWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}

void CustomWindow::addFilter() {

}

void CustomWindow::rmvFilter() {

}

void CustomWindow::move_Up() {

}

void CustomWindow::move_Down() {

}

void CustomWindow::changeCategory(int cat) {

}

void CustomWindow::setFilter() {
    
}
