#include"pref_window.hpp"
#include"debug_window.hpp"
#include"main_window.hpp"
#include"cat_vec.hpp"
#include"custom_edit.hpp"
#include"new_filter.hpp"
#include"filters/layer_filter.hpp"
#include<QFileDialog>
#include<QColorDialog>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QGroupBox>

PrefWindow::PrefWindow(QWidget *parent) : QDialog(parent)  {
    setWindowTitle("Preferences");
    setMinimumSize(550, 400);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(12);
    
    chk_path = new QCheckBox(tr("Save Directory Paths"), this);
    chk_path->setChecked(settings.value("chk_path").toBool());
    mainLayout->addWidget(chk_path);
    
    QHBoxLayout *pathRow = new QHBoxLayout();
    pathRow->setSpacing(8);
    QLabel *title = new QLabel(tr("Save Filters:"), this);
    custom_path_lbl = new QLabel(tr("Custom Path"), this);
    custom_path_lbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    pref_custom = new QPushButton(tr("..."), this);
    pref_custom->setFixedWidth(50);
    connect(pref_custom, SIGNAL(clicked()), this, SLOT(pref_setPath()));
    pathRow->addWidget(title);
    pathRow->addWidget(custom_path_lbl);
    pathRow->addWidget(pref_custom);
    mainLayout->addLayout(pathRow);
    
    QString fname = settings.value("chk_filename").toString();
    if(fname != "") {
        custom_path_lbl->setText(fname);
        loaded = true;
    }
    
    QGroupBox *fracGroup = new QGroupBox(tr("Fractal Settings"), this);
    QGridLayout *fracLayout = new QGridLayout(fracGroup);
    fracLayout->setSpacing(8);
    
    QLabel *lbl_1 = new QLabel(tr("Real:"), this);
    frac_real = new QLineEdit(this);
    frac_real->setText("-0.743643887032151");
    frac_real->setToolTip(tr("Center Real"));
    
    QLabel *lbl_2 = new QLabel(tr("Imag:"), this);
    frac_imag = new QLineEdit(this);
    frac_imag->setText("0.142625924205330");
    frac_imag->setToolTip(tr("Center Imag:"));
    
    QLabel *lbl_3 = new QLabel(tr("Zoom:"), this);
    frac_zoom = new QLineEdit(this);
    frac_zoom->setText("1");
    frac_zoom->setToolTip(tr("Fractal Zoom"));
    
    QLabel *lbl_4 = new QLabel(tr("Iterations:"), this);
    frac_iter = new QLineEdit(this);
    frac_iter->setText("100");
    frac_iter->setToolTip(tr("Fractal Iterations"));
    
    QLabel *lbl_5 = new QLabel(tr("Zoom Speed:"), this);
    frac_speed = new QLineEdit(this);
    frac_speed->setText("100");
    frac_speed->setToolTip(tr("Speed of Zoom for animation"));
    
    QLabel *lbl_6 = new QLabel(tr("Max Zoom:"), this);
    frac_max = new QLineEdit(this);
    frac_max->setText("250000");
    frac_max->setToolTip(tr("Max depth of zoom"));
    
    fracLayout->addWidget(lbl_1, 0, 0);
    fracLayout->addWidget(frac_real, 0, 1);
    fracLayout->addWidget(lbl_2, 0, 2);
    fracLayout->addWidget(frac_imag, 0, 3);
    fracLayout->addWidget(lbl_3, 1, 0);
    fracLayout->addWidget(frac_zoom, 1, 1);
    fracLayout->addWidget(lbl_4, 1, 2);
    fracLayout->addWidget(frac_iter, 1, 3);
    fracLayout->addWidget(lbl_5, 2, 0);
    fracLayout->addWidget(frac_speed, 2, 1);
    fracLayout->addWidget(lbl_6, 2, 2);
    fracLayout->addWidget(frac_max, 2, 3);
    mainLayout->addWidget(fracGroup);
    
    QHBoxLayout *chromaRow = new QHBoxLayout();
    chromaRow->setSpacing(8);
    QLabel *tmp_lbl2 = new QLabel(tr("Chroma Key:"), this);
    
    QColor color(50,50,35);
    QVariant variant = color;
    QString color_var = variant.toString();
    color_start = new QLabel(this);
    color_start->setFixedSize(50, 25);
    color_start->setStyleSheet("QLabel { background-color :" + color_var + " ; }");
    color_start_btn = new QPushButton("...", this);
    color_start_btn->setFixedWidth(30);
    connect(color_start_btn, SIGNAL(clicked()), this, SLOT(grab_color1()));
    
    QLabel *tmp_lbl = new QLabel(tr("to"), this);
    
    QColor color2(255, 255, 85);
    variant = color2;
    QString color_var2 = variant.toString();
    color_stop = new QLabel(this);
    color_stop->setFixedSize(50, 25);
    color_stop->setStyleSheet("QLabel { background-color: " + color_var2 + "; }");
    color_stop_btn = new QPushButton("...", this);
    color_stop_btn->setFixedWidth(30);
    connect(color_stop_btn, SIGNAL(clicked()), this, SLOT(grab_color2()));
    
    chromaRow->addWidget(tmp_lbl2);
    chromaRow->addWidget(color_start);
    chromaRow->addWidget(color_start_btn);
    chromaRow->addWidget(tmp_lbl);
    chromaRow->addWidget(color_stop);
    chromaRow->addWidget(color_stop_btn);
    chromaRow->addStretch();
    mainLayout->addLayout(chromaRow);
    
    show_debug = new QCheckBox(tr("Show Debug on Startup"), this);
    show_debug->setChecked(settings.value("chk_dbg", true).toBool());
    mainLayout->addWidget(show_debug);
    
    mainLayout->addStretch();
    
    QHBoxLayout *btnRow = new QHBoxLayout();
    btnRow->setSpacing(8);
    pref_save = new QPushButton(tr("Save"), this);
    pref_save->setMinimumWidth(75);
    connect(pref_save, SIGNAL(clicked()), this, SLOT(pref_Save()));
    pref_cancel = new QPushButton(tr("Cancel"), this);
    pref_cancel->setMinimumWidth(75);
    connect(pref_cancel, SIGNAL(clicked()), this, SLOT(pref_Cancel()));
    btnRow->addWidget(pref_save);
    btnRow->addWidget(pref_cancel);
    btnRow->addStretch();
    mainLayout->addLayout(btnRow);
    
    setLayout(mainLayout);
}

int PrefWindow::findIn(const std::string &n) {
    for(size_t i = 0; i < new_filter_list.size(); ++i) {
       if(new_filter_list[i].name == n)
            return i;
    }
    return -1;
}


void PrefWindow::grab_color1() {
    QColorDialog *dialog = new QColorDialog(this);
    QColor color=  dialog->getColor();
    QVariant variant = color;
    QString color_var = variant.toString();
    cv::Scalar color_s (color.blue(), color.green(), color.red());
    color_start->setStyleSheet("QLabel { background-color :" + color_var + " ; }");
    int filter_f = findIn("New_Layer_0_GreenScreen");
    if(filter_f != -1) {
        try {
            BackgroundReplacementEffect *bg_e = dynamic_cast<BackgroundReplacementEffect *>(new_filter_list[filter_f].filter);
            bg_e->setLow(color_s);
        } catch(...) {

        }
    }
    filter_f = findIn("New_Layer_0_GreenScreen_Opposite");
    if(filter_f != -1) {
        try {
            GreenScreenEffect *g_e = dynamic_cast<GreenScreenEffect *>(new_filter_list[filter_f].filter);
            g_e->setLow(color_s);
        }
        catch(...) {

        }
    }

}

void PrefWindow::grab_color2() {
    QColorDialog *dialog = new QColorDialog(this);
    QColor color=  dialog->getColor();
    QVariant variant = color;
    QString color_var = variant.toString();
    cv::Scalar color_s (color.blue(), color.green(), color.red());
    color_stop->setStyleSheet("QLabel { background-color :" + color_var + " ; }");
    int filter_f = findIn("New_Layer_0_GreenScreen");
    if(filter_f != -1) {
        try {
            BackgroundReplacementEffect *bg_e = dynamic_cast<BackgroundReplacementEffect *>(new_filter_list[filter_f].filter);
            bg_e->setHigh(color_s);
        } 
        catch(...) {

        }
    }
    filter_f = findIn("New_Layer_0_GreenScreen_Opposite");
    if(filter_f != -1) {
        try {
            GreenScreenEffect *g_e = dynamic_cast<GreenScreenEffect *>(new_filter_list[filter_f].filter);
            g_e->setHigh(color_s);
        }
        catch(...) {

        }
    }
}

void PrefWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}

void PrefWindow::pref_Save() {
    settings.setValue("chk_path", chk_path->isChecked());  
    settings.setValue("chk_dbg", show_debug->isChecked());
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