#include"custom_edit.hpp"

CustomEditWindow::CustomEditWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(320, 240);

    filter_names = new QComboBox(this);
    filter_names->setGeometry(25, 30, 320-250, 30);
}
    
void CustomEditWindow::updateFilterNames() {

}








