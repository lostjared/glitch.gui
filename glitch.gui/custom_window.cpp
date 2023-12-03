#include"custom_window.hpp"
#include"main_window.hpp"
#include"cat_vec.hpp"
#include"new_filter.hpp"


CustomWindow::CustomWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(640, 480);
    filter_cat = new QComboBox(this);
    filter_cat->setGeometry(15, 15, (640-15-15), 25);
    filter = new QComboBox(this);
    filter->setGeometry(15, 15+25+5, (640-15-15), 25);

    filter_custom = new QListWidget(this);
    filter_custom->setGeometry(15, 15+25+5+25+5, (640-15-15), 300);

    btn_add = new QPushButton(tr("Add"), this);
    btn_add->setGeometry(15, 15+25+5+25+5+300+5, 100, 25);

    connect(btn_add, SIGNAL(clicked()), this, SLOT(addFilter()));

    btn_rmv = new QPushButton(tr("Remove"), this);
    btn_rmv->setGeometry(15+100+5, 15+25+5+25+5+300+5, 100, 25);

    connect(btn_rmv, SIGNAL(clicked()), this, SLOT(rmvFilter()));

    btn_up = new QPushButton(tr("Move Up"), this);
    btn_up->setGeometry(15+100+5+100+5, 15+25+5+25+5+300+5, 100, 25);

    connect(btn_up, SIGNAL(clicked()), this, SLOT(move_Up()));

    btn_down = new QPushButton(tr("Move Down"), this);
    btn_down->setGeometry(15+100+5+100+5+100+5, 15+25+5+25+5+300+5, 100, 25);

    connect(btn_down, SIGNAL(clicked()), this, SLOT(move_Down()));

    QLabel *f_name = new QLabel(tr("Name: "), this);
    f_name->setGeometry(25, 15+25+5+25+5+300+5+25+5+10+5, 100, 25);

    filter_name = new QLineEdit(this);
    filter_name->setGeometry(50+25+5, 15+25+5+25+5+300+5+25+5+10+5, 200, 25);

    btn_set = new QPushButton(tr("Set Filter"), this);
    btn_set->setGeometry(640-125-5, 15+25+5+25+5+300+5+25+5+10+5, 100, 25);

    connect(btn_set, SIGNAL(clicked()), this, SLOT(setFilter()));
    connect(filter_cat, SIGNAL(currentIndexChanged(int)), this, SLOT(changeCategory(int)));
    setWindowTitle("Create Custom Filter");

    filter_cat->addItem(tr("In order"));
    filter_cat->addItem(tr("Sorted"));
    filter_cat->addItem(tr("Fast"));
    filter_cat->addItem(tr("Glitch"));
    filter_cat->addItem(tr("Mirror"));
    filter_cat->addItem(tr("New Filter"));

    loadCategory(0);
}

void CustomWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}

void CustomWindow::addFilter() {
    int index = filter->currentIndex();
    if(index >= 0) {
        QString val = filter->itemText(index);
        filter_custom->addItem(val);        
    }
}

void CustomWindow::rmvFilter() {
    int index = filter_custom->currentRow();
    if(index >= 0) {
        filter_custom->takeItem(index);
    }
}

void CustomWindow::move_Up() {
    int index = filter_custom->currentRow();
    if(index >= 0) {
        QListWidgetItem *item = filter_custom->item(index);
        if(index-1 >= 0) {
            QListWidgetItem *item2 = filter_custom->item(index-1);
            QString data[2];
            data[0] = item->text();
            data[1] = item2->text();
            item->setText(data[1]);
            item2->setText(data[0]);
            filter_custom->setCurrentRow(index-1);
        }
    }
}

void CustomWindow::move_Down() {

}

void CustomWindow::loadCategory(int index) {
    filter->clear();
    if(index == 5) {
        auto *a = &new_filter_list;
        for(int i = 0; i < static_cast<int>(a->size()); ++i) {
            filter->addItem(a->at(i).name);
        }
    } else {
        std::vector<std::string> *v = vec_cat[index];
        for(int i = 0; i < static_cast<int>(v->size()); ++i) {
            std::string s = v->at(i);
            if(s.find("InOrder") == std::string::npos)
                filter->addItem(v->at(i).c_str());
        }
    }
    filter->setCurrentIndex(0);
}

void CustomWindow::changeCategory(int) {
    int index = filter_cat->currentIndex();
    loadCategory(index);
}

void CustomWindow::setFilter() {

}
