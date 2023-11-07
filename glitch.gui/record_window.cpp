#include"record_window.hpp"
#include"main_window.hpp"
#include"display_window.hpp"
#include<QFileDialog>
#include<QFile>
#include<QMessageBox>
#include<sstream>

RecordWindow::RecordWindow(QWidget *parent) : QDialog(parent) {
    setGeometry(1200, 100, 460, 220);
    setFixedSize(460, 220);
    setWindowTitle(tr("Record Options"));
    
    QLabel *ff_lbl = new QLabel(tr("FFFMpeg path:"), this);
    ff_lbl->setGeometry(25, 25, 100, 25);
    ffmpeg_path = new QLineEdit(this);
#if defined(_WIN32)
    ffmpeg_path->setText("ffmpeg");
#elif defined(__linux__)
    ffmpeg_path->setText("/usr/bin/ffmpeg");
#elif defined(__APPLE__)
    ffmpeg_path->setText("/usr/local/bin/ffmpeg");
#endif

    ffmpeg_path->setGeometry(25+100,25,225,25);

    ffmpeg_man = new QCheckBox(tr("Set Path"), this);
    ffmpeg_man->setGeometry(25+100+225+10, 25, 100, 25);

    ffmpeg_path->setEnabled(false);

    connect(ffmpeg_man, SIGNAL(clicked()), this, SLOT(setPath()));
    
    QLabel *ff_type = new QLabel(tr("Codec: "), this);
    ff_type->setGeometry(25, 75, 50, 25);
    ffmpeg_type = new QComboBox(this);
    ffmpeg_type->setGeometry(25+50, 75, 100, 25);
    ffmpeg_type->addItem(tr("x264"));
    ffmpeg_type->addItem(tr("x265"));
    ffmpeg_type->addItem(tr("PNG"));
    QLabel *lbl_crf = new QLabel(tr("CRF"), this);
    lbl_crf->setGeometry(180, 75, 50, 25);

    ffmpeg_crf = new QLineEdit(this);
    ffmpeg_crf->setText("24");
    ffmpeg_crf->setGeometry(180+50+5, 75, 100, 25);

    settings_save = new QPushButton(tr("Save"), this);
    settings_save->setGeometry(width()-125,height()-45, 100, 25);

    connect(settings_save, SIGNAL(clicked()), this, SLOT(saveSettings()));

    QLabel *ff_fps = new QLabel(tr("FPS: "), this);
    ff_fps->setGeometry(25, 105, 50, 25);

    ffmpeg_fps = new QLineEdit(this);
    ffmpeg_fps->setGeometry(75, 105, 100, 25);
    ffmpeg_fps->setText(tr("30"));

    ffmpeg_same = new QCheckBox(this);
    ffmpeg_same->setGeometry(185,105,120,25);
    ffmpeg_same->setText(tr("Same as Source"));
    ffmpeg_same->setChecked(true);
    ffmpeg_fps->setEnabled(false);

    connect(ffmpeg_same, SIGNAL(clicked()), this, SLOT(chkStateChanged()));

    ffmpeg_file = new QLabel(tr("Select File Path"), this);
    ffmpeg_file->setGeometry(25,105+25+5, 300, 25);
    ffmpeg_file_set = new QPushButton(tr("Select"), this);
    ffmpeg_file_set->setGeometry(25+310,105+25+5,100,25);

    connect(ffmpeg_file_set, SIGNAL(clicked()), this, SLOT(selectPath()));
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}

void RecordWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}

void RecordWindow::setPath() {
    if(ffmpeg_man->isChecked()) {
        ffmpeg_path->setEnabled(true);
    } else {
        ffmpeg_path->setEnabled(false);
    }
}

void RecordWindow::saveSettings() {
    int crf = ffmpeg_crf->text().toInt();
    QFile f(ffmpeg_path->text());

    if(ffmpeg_man->isChecked()) {
        rec_info.ffmpeg_path = ffmpeg_path->text().toStdString();
    } else {
        rec_info.ffmpeg_path = "ffmpeg";
    }

    if(crf < 10 || crf > 40) {
        QMessageBox msgbox;    
        msgbox.setWindowTitle(tr("Error invalid CRF value"));
        msgbox.setIcon(QMessageBox::Icon::Critical);
        msgbox.setWindowIcon(QIcon(":/images/icon.png"));
        msgbox.setText(tr("Invalid CRF Value\n"));
        msgbox.exec();
        return; 
    }

    if(ffmpeg_man->isChecked() && !f.exists()) {
        QMessageBox msgbox;    
        msgbox.setWindowTitle(tr("Error invalid path"));
        msgbox.setIcon(QMessageBox::Icon::Critical);
        msgbox.setWindowIcon(QIcon(":/images/icon.png"));
        msgbox.setText(tr("Invalid path to ffmpeg is it installed?\nMaybe try /usr/local/bin/ffmpeg or\n/usr/bin/ffmpeg\n"));
        msgbox.exec();
        return;
    }

    if(path_selected == false) {
        QMessageBox msgbox;    
        msgbox.setWindowTitle(tr("Error invalid path"));
        msgbox.setIcon(QMessageBox::Icon::Critical);
        msgbox.setWindowIcon(QIcon(":/images/icon.png"));
        msgbox.setText(tr("You must select path for outputted videos click Select and choose a directory.\n"));
        msgbox.exec();
        return;
    }

    rec_info.crf = ffmpeg_crf->text().toStdString();
    rec_info.save_png = false;

    std::ostringstream stream;
    stream << ffmpeg_file->text().toStdString();
    rec_info.filename = stream.str();
   
    switch(ffmpeg_type->currentIndex()) {
        case 0:
            rec_info.codec = "libx264";
        break;
        case 1:
            rec_info.codec = "libx265";
        break;
        case 2:
            rec_info.save_png = true;
            rec_info_set = true;
            main_window->enableRecord();
            hide();
            return;
        break;
    }

     if(ffmpeg_same->isChecked()){
        rec_info.fps = "same";
    } else {
        rec_info.fps = ffmpeg_fps->text().toStdString();
    }
    rec_info_set = true;
    main_window->enableRecord();
    hide();
}

void RecordWindow::chkStateChanged() {
    if(ffmpeg_same->checkState() == Qt::Checked) {
        ffmpeg_fps->setEnabled(false);
    } else {
        ffmpeg_fps->setEnabled(true);
    }
}

void RecordWindow::selectPath() {
    QString dir;
    dir = QFileDialog::getExistingDirectory(this, tr("Open Dir"), "");
    if(dir != "") {
        ffmpeg_file->setText(dir);
        path_selected = true;
    }
}
