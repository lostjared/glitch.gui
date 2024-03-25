#include"pref_window.hpp"
#include"debug_window.hpp"
#include"main_window.hpp"
#include"cat_vec.hpp"
#include"custom_edit.hpp"
#include"new_filter.hpp"
#include"filters/layer_filter.hpp"
#include<QFileDialog>
#include<QColorDialog>

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
   //cv::Scalar lowerGreen(35, 50, 50);
   ///cv::Scalar upperGreen(85, 255, 255);
    QColor color(50,50,35);
    QVariant variant = color;
    QString color_var = variant.toString();
    QColor color2(255, 255, 85);
    variant = color2;
    QString color_var2 = variant.toString();   
    color_start = new QLabel(this);
    color_start->setGeometry(25,250, 50, 25);
    color_start->setStyleSheet("QLabel { background-color :" + color_var + " ; }");
    color_start_btn = new QPushButton("...", this);
    color_start_btn->setGeometry(80,250,25,25);
    QLabel *tmp_lbl = new QLabel(tr(" to "), this);
    tmp_lbl->setGeometry(110,250,25,25);
    color_stop = new QLabel(this);
    color_stop->setStyleSheet("QLabel { background-color: " + color_var2 + "; }");
    color_stop->setGeometry(140,250,50,25);
    color_stop_btn = new QPushButton("...", this);
    color_stop_btn->setGeometry(140+50+5, 250, 25, 25);
    QLabel *tmp_lbl2 = new QLabel(tr("Chroma Key: "), this);
    tmp_lbl2->setGeometry(25, 215, 100, 25);

    connect(color_start_btn, SIGNAL(clicked()), this, SLOT(grab_color1()));
    connect(color_stop_btn, SIGNAL(clicked()), this, SLOT(grab_color2()));

    show_debug = new QCheckBox(tr("SHow Debug on Startup"), this);
    show_debug->setGeometry(15, 300, 200, 25);
    show_debug->setChecked(settings.value("chk_dbg", true).toBool());
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