#include"pref_window.hpp"
#include"debug_window.hpp"
#include"main_window.hpp"
#include"cat_vec.hpp"
#include"custom_edit.hpp"
#include<QFileDialog>

PrefWindow::PrefWindow(QWidget *parent) : QDialog(parent)  {
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
    QLabel *lbl_1 = new QLabel(tr("Fractal Real: "), this);
    lbl_1->setGeometry(25, 100, 100, 25);
    frac_real = new QLineEdit(this);
    frac_real->setGeometry(125, 100, 100, 25);
    QLabel *lbl_2 = new QLabel(tr("Fractal Imag: "), this);
    lbl_2->setGeometry(250, 100, 100, 25);
    frac_imag = new QLineEdit(this);
    frac_imag->setGeometry(400, 100, 100, 25);
    QLabel *lbl_3 =new QLabel(tr("Fractal Zoom: "), this);
    lbl_3->setGeometry(25, 130, 100, 25);
    frac_zoom = new QLineEdit(this);
    frac_zoom->setGeometry(125, 130, 100, 25);
    QLabel *lbl_4 = new QLabel(tr("Iterations: "), this);
    lbl_4->setGeometry(250, 130, 100, 25);
    frac_iter = new QLineEdit(this);
    frac_iter->setGeometry(400, 130, 100,25);

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