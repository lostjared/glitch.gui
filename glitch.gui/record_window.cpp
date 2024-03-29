#include"record_window.hpp"
#include"main_window.hpp"
#include"display_window.hpp"
#include"debug_window.hpp"
#include"pref_window.hpp"
#include<QFileDialog>
#include<QFile>
#include<QMessageBox>
#include<sstream>

extern std::string current_path;

RecordWindow::RecordWindow(QWidget *parent) : QDialog(parent) {
    setGeometry(1200, 100, 460, 220);
    setFixedSize(460, 220);
    setWindowTitle(tr("Record Options"));
    
    QLabel *ff_lbl = new QLabel(tr("FFMpeg path:"), this);
    ff_lbl->setGeometry(25, 25, 100, 25);
    ffmpeg_path = new QLineEdit(this);
    ffmpeg_path->setToolTip(tr("Set path for FFmpeg executable"));
#if defined(_WIN32)
    ffmpeg_path->setText("ffmpeg");
#elif defined(__linux__)
    ffmpeg_path->setText("/usr/bin/ffmpeg");
#elif defined(__APPLE__)
    //std::string p = current_path;
    //p += "ffmpeg";
    //ffmpeg_path->setText(p.c_str());
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
    ffmpeg_type->setToolTip(tr("Codec to use for encoding of video"));
    ffmpeg_type->setGeometry(25+50, 75, 100, 25);
    ffmpeg_type->addItem(tr("x264"));
    ffmpeg_type->addItem(tr("x265"));
    ffmpeg_type->addItem(tr("PNG"));
    QLabel *lbl_crf = new QLabel(tr("CRF"), this);
    lbl_crf->setGeometry(180, 75, 50, 25);

    ffmpeg_crf = new QLineEdit(this);
    ffmpeg_crf->setToolTip(tr("How much compression to use"));
    ffmpeg_crf->setText("24");
    ffmpeg_crf->setGeometry(180+50+5, 75, 100, 25);

    settings_save = new QPushButton(tr("Save"), this);
    settings_save->setToolTip(tr("Save Settings"));
    settings_save->setGeometry(width()-125,height()-45, 100, 25);

    stretch_video = new QCheckBox(tr("Stretch"), this);
    stretch_video->setToolTip(tr("Do you wish to stretch this vieo"));
    stretch_video->setGeometry(25,height()-45, 100, 25);

    stretch_width = new QLineEdit(this);
    stretch_width->setGeometry(125,height()-45,75,25);
    stretch_width->setText("1280");
    stretch_width->setToolTip(tr("Stretch Width"));
    stretch_width->setEnabled(false);

    stretch_height = new QLineEdit(this);
    stretch_height->setGeometry(125+75+10,height()-45, 75,25);
    stretch_height->setText("720");
    stretch_height->setToolTip(tr("Stretch height"));
    stretch_height->setEnabled(false);


    connect(stretch_video, SIGNAL(clicked()), this, SLOT(stateChecked()));
    connect(settings_save, SIGNAL(clicked()), this, SLOT(saveSettings()));

    QLabel *ff_fps = new QLabel(tr("FPS: "), this);
    ff_fps->setGeometry(25, 105, 50, 25);

    ffmpeg_fps = new QLineEdit(this);
    ffmpeg_fps->setToolTip(tr("Frames Per Second"));
    ffmpeg_fps->setGeometry(75, 105, 100, 25);
    ffmpeg_fps->setText(tr("30"));

    ffmpeg_same = new QCheckBox(this);
    ffmpeg_same->setGeometry(185,105,120,25);
    ffmpeg_same->setText(tr("Same as Source"));
    ffmpeg_same->setToolTip(tr("Use same rate as input file"));
    ffmpeg_same->setChecked(true);
    ffmpeg_fps->setEnabled(false);

    connect(ffmpeg_same, SIGNAL(clicked()), this, SLOT(chkStateChanged()));

    ffmpeg_file = new QLabel(tr("Select File Path"), this);
    ffmpeg_file->setGeometry(25,105+25+5, 300, 25);
    ffmpeg_file_set = new QPushButton(tr("Select"), this);
    ffmpeg_file_set->setToolTip(tr("Select Path"));
    ffmpeg_file_set->setGeometry(25+310,105+25+5,100,25);

    connect(ffmpeg_file_set, SIGNAL(clicked()), this, SLOT(selectPath()));
    //setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}

void RecordWindow::stateChecked() {
    if(stretch_video->isChecked()) {
        stretch_width->setEnabled(true);
        stretch_height->setEnabled(true);
    } else {
        stretch_width->setEnabled(false);
        stretch_height->setEnabled(false);
    }
}

bool RecordWindow::ready() {
    if(rec_info_set == true && path_selected == true)
        return true;
    return false;
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
            if(stretch_video->isChecked()) {
                rec_info.stretch = true;
                int w = stretch_width->text().toInt();
                int h = stretch_height->text().toInt();
                if(w > 32 && h > 32) {
                    std::ostringstream stream;
                    stream << w << "x" << h;
                    rec_info.stretch = true;
                    rec_info.stretch_dst = stream.str();
                    rec_info.stretch_width = w;
                    rec_info.stretch_height = h;
                } else { 
                    // Error message
                    QMessageBox msgbox;    
                    msgbox.setWindowTitle(tr("Error invalid size"));
                    msgbox.setIcon(QMessageBox::Icon::Critical);
                    msgbox.setWindowIcon(QIcon(":/images/icon.png"));
                    msgbox.setText(tr("You must enter a valid resolution.\n"));
                    msgbox.exec();
                    return;
                }
            } else {
                rec_info.stretch = false;
            }
            //main_window->enableRecord();
            hide();
            return;
        break;
    }
     if(ffmpeg_same->isChecked()){
        QString text;
        QTextStream stream(&text);
        stream << fps_same;
        rec_info.fps = text.toStdString();
    } else {
        rec_info.fps = ffmpeg_fps->text().toStdString();
    }

    if(stretch_video->isChecked()) {
        int w = stretch_width->text().toInt();
        int h = stretch_height->text().toInt();
        if(w > 32 && h > 32) {
            std::ostringstream stream;
            stream << w << "x" << h;
            rec_info.stretch = true;
            rec_info.stretch_dst = stream.str();
            rec_info.stretch_width = w;
            rec_info.stretch_height = h;
        } else {
             // Error message
             QMessageBox msgbox;    
             msgbox.setWindowTitle(tr("Error invalid size"));
             msgbox.setIcon(QMessageBox::Icon::Critical);
             msgbox.setWindowIcon(QIcon(":/images/icon.png"));
             msgbox.setText(tr("You must enter a valid resolution.\n"));
             msgbox.exec();
            return;
        }
    } else {
        rec_info.stretch = false;
        rec_info.stretch_dst = "";
    }

    rec_info_set = true;
    //main_window->enableRecord();
    main_window->debug_window->Log("gui: Updated record settings...\n");
    if(rec_info.stretch) {
        main_window->debug_window->Log("glitch: Video Stretch: Enabled...\n");
    }
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
    QString path;
    
    if(main_window->pref_window->savePath()) {
        path = settings.value("record_path").toString();
    }

    dir = QFileDialog::getExistingDirectory(this, tr("Open Dir"), path);
    if(dir != "") {
        ffmpeg_file->setText(dir);
        path_selected = true;
        if(main_window->pref_window->savePath())
            settings.setValue("record_path", dir);
    }



}
