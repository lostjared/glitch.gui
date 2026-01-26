#include"record_window.hpp"
#include"main_window.hpp"
#include"display_window.hpp"
#include"debug_window.hpp"
#include"pref_window.hpp"
#include<QFileDialog>
#include<QFile>
#include<QMessageBox>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QScreen>
#include<QApplication>
#include<sstream>

extern std::string current_path;

RecordWindow::RecordWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle(tr("Record Options"));
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(12);
    
    QGridLayout *pathLayout = new QGridLayout();
    pathLayout->setSpacing(8);
    QLabel *ff_lbl = new QLabel(tr("FFMpeg path:"));
    ffmpeg_path = new QLineEdit(this);
    ffmpeg_path->setToolTip(tr("Set path for FFmpeg executable"));
    ffmpeg_path->setMinimumWidth(200);
#if defined(_WIN32)
    ffmpeg_path->setText("ffmpeg");
#elif defined(__linux__)
    ffmpeg_path->setText("/usr/bin/ffmpeg");
#elif defined(__APPLE__)
    ffmpeg_path->setText("/usr/local/bin/ffmpeg");
#endif
    ffmpeg_path->setEnabled(false);
    ffmpeg_man = new QCheckBox(tr("Set Path"));
    connect(ffmpeg_man, SIGNAL(clicked()), this, SLOT(setPath()));
    
    pathLayout->addWidget(ff_lbl, 0, 0);
    pathLayout->addWidget(ffmpeg_path, 0, 1);
    pathLayout->addWidget(ffmpeg_man, 0, 2);
    mainLayout->addLayout(pathLayout);
    
    QGridLayout *codecLayout = new QGridLayout();
    codecLayout->setSpacing(8);
    QLabel *ff_type = new QLabel(tr("Codec:"));
    ffmpeg_type = new QComboBox(this);
    ffmpeg_type->setToolTip(tr("Codec to use for encoding of video"));
    ffmpeg_type->setMinimumWidth(150);
    ffmpeg_type->addItem(tr("x264"));
    ffmpeg_type->addItem(tr("x265"));
    ffmpeg_type->addItem(tr("H.264 NVENC"));
    ffmpeg_type->addItem(tr("HEVC NVENC"));
    ffmpeg_type->addItem(tr("H.264 VAAPI"));
    ffmpeg_type->addItem(tr("HEVC VAAPI"));
    ffmpeg_type->addItem(tr("PNG"));
    connect(ffmpeg_type, SIGNAL(currentIndexChanged(int)), this, SLOT(onCodecChanged(int)));
    
    QLabel *lbl_crf = new QLabel(tr("Quality"));
    ffmpeg_crf = new QSpinBox(this);
    ffmpeg_crf->setToolTip(tr("Compression level (lower=better quality, higher=faster)"));
    ffmpeg_crf->setValue(24);
    ffmpeg_crf->setMinimum(0);
    ffmpeg_crf->setMaximum(51);
    ffmpeg_crf->setMinimumWidth(70);
    
    codecLayout->addWidget(ff_type, 0, 0);
    codecLayout->addWidget(ffmpeg_type, 0, 1);
    codecLayout->addWidget(lbl_crf, 0, 2);
    codecLayout->addWidget(ffmpeg_crf, 0, 3);
    mainLayout->addLayout(codecLayout);
    
    QGridLayout *fpsLayout = new QGridLayout();
    fpsLayout->setSpacing(8);
    QLabel *ff_fps = new QLabel(tr("FPS:"));
    ffmpeg_fps = new QLineEdit(this);
    ffmpeg_fps->setToolTip(tr("Frames Per Second"));
    ffmpeg_fps->setText(tr("30"));
    ffmpeg_fps->setMaximumWidth(100);
    ffmpeg_fps->setEnabled(false);
    
    ffmpeg_same = new QCheckBox(tr("Same as Source"));
    ffmpeg_same->setToolTip(tr("Use same rate as input file"));
    ffmpeg_same->setChecked(true);
    connect(ffmpeg_same, SIGNAL(clicked()), this, SLOT(chkStateChanged()));
    
    fpsLayout->addWidget(ff_fps, 0, 0);
    fpsLayout->addWidget(ffmpeg_fps, 0, 1);
    fpsLayout->addWidget(ffmpeg_same, 0, 2);
    fpsLayout->setColumnStretch(3, 1);
    mainLayout->addLayout(fpsLayout);
    
    QGridLayout *stretchLayout = new QGridLayout();
    stretchLayout->setSpacing(8);
    stretch_video = new QCheckBox(tr("Stretch Video"));
    stretch_video->setToolTip(tr("Do you wish to stretch this video"));
    connect(stretch_video, SIGNAL(clicked()), this, SLOT(stateChecked()));
    
    stretch_width = new QLineEdit(this);
    stretch_width->setText("1280");
    stretch_width->setToolTip(tr("Stretch Width"));
    stretch_width->setMaximumWidth(80);
    stretch_width->setEnabled(false);
    
    stretch_height = new QLineEdit(this);
    stretch_height->setText("720");
    stretch_height->setToolTip(tr("Stretch Height"));
    stretch_height->setMaximumWidth(80);
    stretch_height->setEnabled(false);
    
    stretchLayout->addWidget(stretch_video, 0, 0);
    stretchLayout->addWidget(stretch_width, 0, 1);
    stretchLayout->addWidget(stretch_height, 0, 2);
    stretchLayout->setColumnStretch(3, 1);
    mainLayout->addLayout(stretchLayout);
    
    QHBoxLayout *fileLayout = new QHBoxLayout();
    fileLayout->setSpacing(8);
    ffmpeg_file = new QLabel(tr("Select File Path"));
    ffmpeg_file_set = new QPushButton(tr("Select"));
    ffmpeg_file_set->setToolTip(tr("Select Output Directory"));
    ffmpeg_file_set->setMinimumWidth(100);
    connect(ffmpeg_file_set, SIGNAL(clicked()), this, SLOT(selectPath()));
    
    fileLayout->addWidget(ffmpeg_file);
    fileLayout->addStretch();
    fileLayout->addWidget(ffmpeg_file_set);
    mainLayout->addLayout(fileLayout);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(8);
    buttonLayout->addStretch();
    settings_save = new QPushButton(tr("Save"));
    settings_save->setToolTip(tr("Save Settings"));
    settings_save->setMinimumWidth(100);
    connect(settings_save, SIGNAL(clicked()), this, SLOT(saveSettings()));
    buttonLayout->addWidget(settings_save);
    mainLayout->addLayout(buttonLayout);
    
    setLayout(mainLayout);
    setFixedSize(550, 320);
    
    centerOnScreen();
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

void RecordWindow::centerOnScreen() {
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2 + screenGeometry.x();
    int y = (screenGeometry.height() - height()) / 2 + screenGeometry.y();
    move(x, y);
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
    int crf = ffmpeg_crf->value();
    QFile f(ffmpeg_path->text());

    if(ffmpeg_man->isChecked()) {
        rec_info.ffmpeg_path = ffmpeg_path->text().toStdString();
    } else {
        rec_info.ffmpeg_path = "ffmpeg";
    }

    if(crf < 0 || crf > 51) {
        QMessageBox msgbox;    
        msgbox.setWindowTitle(tr("Error invalid quality value"));
        msgbox.setIcon(QMessageBox::Icon::Critical);
        msgbox.setWindowIcon(QIcon(":/images/icon.png"));
        msgbox.setText(tr("Invalid Quality Value (0-51)\n"));
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

    rec_info.crf = std::to_string(crf);
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
            rec_info.codec = "h264_nvenc";
        break;
        case 3:
            rec_info.codec = "hevc_nvenc";
        break;
        case 4:
            rec_info.codec = "h264_vaapi";
        break;
        case 5:
            rec_info.codec = "hevc_vaapi";
        break;
        case 6:
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

void RecordWindow::onCodecChanged(int index) {
    if(index == 6) {
        ffmpeg_crf->setEnabled(false);
    } else {
        ffmpeg_crf->setEnabled(true);
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
