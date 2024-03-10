#include"pref_window.hpp"
#include"debug_window.hpp"
#include"main_window.hpp"
#include"cat_vec.hpp"
#include"custom_edit.hpp"
#include"new_filter.hpp"
#include"filters/layer_filter.hpp"
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
    QLabel *lbl_5 = new QLabel(tr("Zoom Speed"), this);
    lbl_5->setGeometry(25, 160, 100, 25);
    frac_speed = new QLineEdit(this);
    frac_speed->setGeometry(125, 160, 100, 25);
    QLabel *lbl_6 = new QLabel(tr("Max Zoom"), this);
    lbl_6->setGeometry(250, 160, 100, 25);
    frac_max = new QLineEdit(this);
    frac_max->setGeometry(400, 160, 100, 25);


    frac_real->setText("-0.743643887032151");
    frac_real->setToolTip(tr("Center Real"));
    frac_imag->setText("0.142625924205330");
    frac_imag->setToolTip(tr("Center Imag:"));
    frac_zoom->setText("1");
    frac_zoom->setToolTip(tr("Fractal Zoom"));
    frac_iter->setText("100");
    frac_iter->setToolTip(tr("Fractal Iterations"));
    frac_speed->setText("100");
    frac_speed->setToolTip(tr("Speed of Zoom for animation"));
    frac_max->setText("250000");
    frac_max->setToolTip(tr("Max depth of zoom"));
}

void PrefWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}

void PrefWindow::pref_Save() {
    settings.setValue("chk_path", chk_path->isChecked());  
    auto findIn = [&](const std::string &n) -> int {
        for(size_t i = 0; i < new_filter_list.size(); ++i) {
            if(new_filter_list[i].name == n)
                return i;
        }
        return -1;
    };
    int filter_f = findIn("New_Low_Fractal");
    if(filter_f != -1) {
        Fractal *f = dynamic_cast<Fractal *>(new_filter_list[filter_f].filter);
        double z_real = atof(frac_real->text().toStdString().c_str());
        double z_imag = atof(frac_imag->text().toStdString().c_str());
        double z_zoom = atof(frac_zoom->text().toStdString().c_str());
        int iter = frac_iter->text().toInt();
        double z_speed = atof(frac_speed->text().toStdString().c_str());
        double z_max = atof(frac_max->text().toStdString().c_str());
        f->initValues(z_real, z_imag, z_zoom, iter, z_speed, z_max);
        filter_f = findIn("New_SuperSlow_Fractal");
        if(filter_f != -1) {
            f = dynamic_cast<Fractal *>(new_filter_list[filter_f].filter);
            f->initValues(z_real, z_imag, z_zoom, iter, z_speed, z_max);
        }
    }
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