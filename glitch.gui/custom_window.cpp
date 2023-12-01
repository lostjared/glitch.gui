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
