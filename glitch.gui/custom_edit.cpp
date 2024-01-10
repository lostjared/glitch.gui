#include"custom_edit.hpp"
#include"cat_vec.hpp"
#include<iostream>
#include"main_window.hpp"
#include"debug_window.hpp"
#include"pref_window.hpp"

CustomEditWindow::CustomEditWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(320, 120);
    filter_names = new QComboBox(this);
    filter_names->setGeometry(25, 30, 320-50, 30);
    filter_rmv = new QPushButton(tr("Remove"), this);
    filter_rmv->setGeometry(30, 30+30, 100, 25);
    connect(filter_rmv, SIGNAL(clicked()), this, SLOT(removeCustom()));
    updateFilterNames();
}
    
void CustomEditWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}

void CustomEditWindow::updateFilterNames() {
    filter_names->clear();
    for(size_t i = 0; i < cat_custom.size(); ++i) {
        custom_filter &f = cat_custom[i];
        filter_names->addItem(f.first.c_str());
    }
   if(main_window != nullptr) main_window->catIndexChanged(0);
}

void CustomEditWindow::removeCustom() {
    int index = filter_names->currentIndex();
    if(index >= 0) { 
        QString name = filter_names->itemText(index);
        auto pos = cat_custom_index.find(name.toStdString());
        if(pos != cat_custom_index.end()) {
            std::string name = pos->first;
            int spot = pos->second;
            std::vector<custom_filter>::iterator i = cat_custom.begin()+spot;
            cat_custom.erase(i);
            cat_custom_index.erase(pos);        
        }
        save_custom(main_window->pref_window->custom_path_lbl->text().toStdString());
        updateFilterNames();
        main_window->debug_window->Log("gui: Removed custom filter: " + name + "\n");
    }  
}






