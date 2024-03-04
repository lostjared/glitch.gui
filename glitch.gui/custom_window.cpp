#include"custom_window.hpp"
#include"main_window.hpp"
#include"cat_vec.hpp"
#include"new_filter.hpp"
#include"custom_edit.hpp"
#include"debug_window.hpp"
#include"pref_window.hpp"
#include<QMessageBox>
#include<QFileDialog>


CustomWindow::CustomWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(640, 510);
    filter_cat = new QComboBox(this);
    filter_cat->setToolTip(tr("Filter CategorieS"));
    filter_cat->setGeometry(15, 15, (640-15-15), 25);
    filter = new QComboBox(this);
    filter->setToolTip(tr("List of Filters"));
    filter->setGeometry(15, 15+25+5, (640-15-15), 25);

    filter_custom = new QListWidget(this);
    filter_custom->setToolTip(tr("List of Selected Filters"));
    filter_custom->setGeometry(15, 15+25+5+25+5, (640-15-15), 300);

    btn_add = new QPushButton(tr("Add"), this);
    btn_add->setToolTip(tr("Add to List"));
    btn_add->setGeometry(15, 15+25+5+25+5+300+5, 100, 25);

    connect(btn_add, SIGNAL(clicked()), this, SLOT(addFilter()));

    btn_rmv = new QPushButton(tr("Remove"), this);
    btn_rmv->setToolTip(tr("Remove from List"));

    btn_rmv->setGeometry(15+100+5, 15+25+5+25+5+300+5, 100, 25);

    connect(btn_rmv, SIGNAL(clicked()), this, SLOT(rmvFilter()));

    btn_up = new QPushButton(tr("Move Up"), this);
    btn_up->setToolTip(tr("Move Selected Filter up in List"));
    btn_up->setGeometry(15+100+5+100+5, 15+25+5+25+5+300+5, 100, 25);

    connect(btn_up, SIGNAL(clicked()), this, SLOT(move_Up()));

    btn_down = new QPushButton(tr("Move Down"), this);
    btn_down->setToolTip(tr("Move Select Filter Down in List"));
    btn_down->setGeometry(15+100+5+100+5+100+5, 15+25+5+25+5+300+5, 100, 25);

    connect(btn_down, SIGNAL(clicked()), this, SLOT(move_Down()));

    btn_playlist = new QPushButton(tr("Save Playlist"), this);
    btn_playlist->setToolTip(tr("Save as Playlist"));
    btn_playlist->setGeometry(15+100+5+100+5+100+5+100+5, 15+25+5+25+5+300+5, 100, 25);

    connect(btn_playlist, SIGNAL(clicked()), this, SLOT(setPlaylist()));

    QLabel *f_name = new QLabel(tr("Name: "), this);
    f_name->setGeometry(25, 15+25+5+25+5+300+5+25+5+10+5, 100, 25);

    filter_name = new QLineEdit(this);
    filter_name->setToolTip(tr("Filter name"));
    filter_name->setGeometry(50+25+5, 15+25+5+25+5+300+5+25+5+10+5, 200, 25);

    btn_set = new QPushButton(tr("Set Filter"), this);
    btn_set->setGeometry(640-125-5, 15+25+5+25+5+300+5+25+5+10+5, 100, 25);
    btn_set->setToolTip(tr("Add as new Custom Filter"));

    btn_update = new QPushButton(tr("Update"), this);
    btn_update->setGeometry(640-225-15, 15+25+5+25+5+300+5+25+5+10+5, 100, 25);
    btn_update->setToolTip(tr("Update custom"));


    chk_r = new QCheckBox(tr("Red"), this);
    chk_r->setGeometry(15,15+25+5+25+5+300+5+25+5+10+5+25+20,50, 25);
    chk_r->setToolTip("Use R Channel");
    //chk_r->setChecked(true);
    chk_r->setToolTip(tr("Restore Red Channel After Filter"));

    chk_g = new QCheckBox(tr("Green"), this);
    chk_g->setGeometry(65,15+25+5+25+5+300+5+25+5+10+5+25+20,60, 25);
    chk_g->setToolTip("Use G Channel");
    //chk_g->setChecked(true);
    chk_g->setToolTip(tr("Restore Green Channel After Filter"));


    chk_b = new QCheckBox(tr("Blue"), this);
    chk_b->setGeometry(65+50+15,15+25+5+25+5+300+5+25+5+10+5+25+20,60,25);
    chk_b->setToolTip("Use R Channel");
    chk_b->setToolTip(tr("Restore Blue Channel After Filter"));

    //chk_b->setChecked(true);

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

QString CustomWindow::getRGB() {
    QString value = "";
    if(chk_r->isChecked()) {
        value += "R";
    }
    if(chk_g->isChecked()) {
        value += "G";
    }
    if(chk_b->isChecked()) {
        value += "B";
    }        

    return value;
}


void CustomWindow::addItem(const QString &text) {
   QString value = getRGB();
    QString ftext;
    if(value.length() > 0) {
        ftext = text + ":" + value;
    } else {
        ftext = text;
    } 
    if(text.toStdString().find("Custom__") != std::string::npos)
        filter_custom->addItem(text);
    else
        filter_custom->addItem(ftext);
}

void CustomWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}

void CustomWindow::addFilter() {
    int index = filter->currentIndex();
    if(index >= 0) {
        QString val = filter->itemText(index);
        QString value = getRGB();
        QString ftext;
        if(value.length() > 0) {
            ftext = val + ":" + value;
         } else {
            ftext = val;
        }
        filter_custom->addItem(ftext);     
        main_window->debug_window->Log("gui: Added " + val + " to custom.\n");   
    }
}

void CustomWindow::rmvFilter() {
    int index = filter_custom->currentRow();
    if(index >= 0) {
        QListWidgetItem *itm = filter_custom->takeItem(index);
        main_window->debug_window->Log("gui: Removed " + itm->text() + " from custom.\n");

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
            main_window->debug_window->Log("gui: Moved filter up in Custom filter list.\n");
        }
    }
}

void CustomWindow::move_Down() {
    int index = filter_custom->currentRow();
    if(index+1 < filter_custom->count()) {
        QListWidgetItem *it1 = filter_custom->item(index);
        QListWidgetItem *it2 = filter_custom->item(index+1);        
        QString data[2];
        data[0] = it1->text();
        data[1] = it2->text();
        it1->setText(data[1]);
        it2->setText(data[0]);
        filter_custom->setCurrentRow(index+1);
        main_window->debug_window->Log("gui: Moved filter down in Custom filter list.\n");
    }
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
    QString name = filter_name->text();
    if(createCustom(name)) {
        QMessageBox box;
        box.setWindowTitle(tr(APP_NAME));
        box.setText("Created custom: " + name);
        box.setWindowIcon(QIcon(":/images/icon.png"));
        box.setIcon(QMessageBox::Icon::Information);
        box.exec();
    } else {
       QMessageBox box;
        box.setWindowTitle(tr(APP_NAME));
        box.setText("Error creating custom No data? no Name?");
        box.setWindowIcon(QIcon(":/images/icon.png"));
        box.setIcon(QMessageBox::Icon::Critical);
        box.exec(); 
    }
}

bool CustomWindow::createCustom(const QString &name) {
    if(name.length() == 0) 
        return false;
    
    if(custom_exists("Custom__" + name.toStdString())) {
        QMessageBox box;
        box.setWindowTitle(APP_NAME);
        box.setText("Error custom name already defined");
        box.setWindowIcon(QIcon(":/images/icon.png"));
        box.setIcon(QMessageBox::Icon::Warning);
        box.exec();
        return false;
    }
    
    std::vector<Custom_Filter> custom_data;
    for(int i = 0; i < filter_custom->count(); ++i) {
        auto data = filter_custom->item(i);
        custom_data.push_back(Custom_Filter(data->text().toStdString()));
    }
    if(custom_data.size()==0)
        return false;

    QString fname = "Custom__" + name;
    cat_custom.push_back(std::make_pair(fname.toStdString(), custom_data));
    custom_setup_map(false);
    save_custom(main_window->pref_window->custom_path_lbl->text().toStdString());
    main_window->custom_edit->updateFilterNames();
    main_window->debug_window->Log("gui: Created new custom filter: " + fname + "\n");
    return true;
}

void CustomWindow::setPlaylist() {

    if(filter_custom->count() <= 0) {
        QMessageBox box;
        box.setWindowTitle(tr(APP_NAME));
        box.setText("Playlist Requires at least one filter...\n");
        box.setWindowIcon(QIcon(":/images/icon.png"));
        box.setIcon(QMessageBox::Icon::Information);
        box.exec();
        return;
    }

  QString path = "";
  QString filename = QFileDialog::getSaveFileName(this,tr("Save Playlist"), path, tr("Playlist Files (*.key *.txt"));
  if(filename != "") {
        if(!cat_playlist.empty()) {
            cat_playlist.erase(cat_playlist.begin(), cat_playlist.end());
        }
   
        if(!cat_playlist_index.empty()) {
                cat_playlist_index.erase(cat_playlist_index.begin(), cat_playlist_index.end());
         }

        for(int i = 0; i < filter_custom->count(); ++i) {
            auto *item = filter_custom->item(i);
            cat_playlist.push_back(item->text().toStdString());
        }
        save_playlist(filename.toStdString());
        main_window->initPlaylist();

        QMessageBox box;
        box.setWindowTitle(tr(APP_NAME));
        box.setText("Playlist Saved and Loaded...\n");
        box.setWindowIcon(QIcon(":/images/icon.png"));
        box.setIcon(QMessageBox::Icon::Information);
        box.exec();
        return;
    }
}