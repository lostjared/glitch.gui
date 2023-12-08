#include"custom_edit.hpp"
#include"cat_vec.hpp"

CustomEditWindow::CustomEditWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(320, 120);
    filter_names = new QComboBox(this);
    filter_names->setGeometry(25, 30, 320-50, 30);
    filter_rmv = new QPushButton(tr("Remove"), this);
    filter_rmv->setGeometry(30, 30+30, 100, 25);
    connect(filter_rmv, SIGNAL(clicked()), this, SLOT(removeCustom()));
    updateFilterNames();
}
    
void CustomEditWindow::updateFilterNames() {
    filter_names->clear();
    for(size_t i = 0; i < cat_custom.size(); ++i) {
        custom_filter &f = cat_custom[i];
        filter_names->addItem(f.first.c_str());
    }
}

void CustomEditWindow::removeCustom() {

  
}






