#include"pref_window.hpp"
#include"debug_window.hpp"
#include"main_window.hpp"
#include"cat_vec.hpp"
#include"custom_edit.hpp"
#include<QFileDialog>

PrefWindow::PrefWindow(QWidget *parent) : QDialog(parent), settings("LostSideDead", "glitch.gui") {
    setFixedSize(640, 480);
    setWindowTitle("Preferences");

    chk_path = new QCheckBox(tr("Save Directory Paths"), this);
    chk_path->setGeometry(25,25,200,25);

    pref_save = new QPushButton(tr("Save"), this);
    pref_save->setGeometry(25,height()-40,75,25);

    pref_cancel = new QPushButton(tr("Cancel"), this);
    pref_cancel->setGeometry(120, height()-40, 75, 25);

    connect(pref_save, SIGNAL(clicked()), this, SLOT(pref_Save()));
    connect(pref_cancel, SIGNAL(clicked()), this, SLOT(pref_Cancel()));

    QLabel *title = new QLabel(tr("Save Filters: "), this);
    title->setGeometry(25,60,100,25);

    custom_path_lbl = new QLabel(tr("Custom Path"), this);
    custom_path_lbl->setGeometry(125,60,200,25);

    pref_custom = new QPushButton(tr("..."), this);
    pref_custom->setGeometry(350, 60, 70, 25);

    connect(pref_custom, SIGNAL(clicked()), this, SLOT(pref_setPath()));
    
    chk_path->setChecked(settings.value("chk_path").toBool());

    QString fname = settings.value("chk_filename").toString();
    if(fname != "") {
        custom_path_lbl->setText(fname);
        loaded = true;
    } 
}

void PrefWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}

void PrefWindow::pref_Save() {
    settings.setValue("chk_path", chk_path->isChecked());   
    hide(); 
    main_window->debug_window->Log("gui: Preferences saved.\n");
}

void PrefWindow::pref_Cancel() {
    hide();
}

bool PrefWindow::savePath() const {
    return chk_path->isChecked();
}


void PrefWindow::pref_setPath() {
    QString filename = QFileDialog::getSaveFileName(this,tr("Open Pref"), "/", tr("Custom Save File (*.dat)"));
    if(filename != "") {
        settings.setValue("chk_filename", filename);
        custom_path_lbl->setText(filename);
        main_window->debug_window->Log("gui: custom save file set to path: " + filename + "\n");
        clear_custom();
        main_window->custom_edit->updateFilterNames();
    }
}