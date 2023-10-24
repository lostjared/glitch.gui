#include"record_window.hpp"
#include"main_window.hpp"
#include<QFileDialog>


RecordWindow::RecordWindow(QWidget *parent) : QDialog(parent) {
    setGeometry(1200, 100, 460, 220);
    setWindowTitle(tr("Record Options"));
    
    QLabel *ff_lbl = new QLabel(tr("FFFMpeg path:"), this);
    ff_lbl->setGeometry(25, 25, 100, 25);
    ffmpeg_path = new QLineEdit(this);
    ffmpeg_path->setText("ffmpeg");
    ffmpeg_path->setGeometry(25+100,25,300,25);
    
    QLabel *ff_type = new QLabel(tr("Codec: "), this);
    ff_type->setGeometry(25, 75, 50, 25);
    ffmpeg_type = new QComboBox(this);
    ffmpeg_type->setGeometry(25+50, 75, 100, 25);
    ffmpeg_type->addItem(tr("x264"));
    ffmpeg_type->addItem(tr("x265"));

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
    ffmpeg_same->setChecked(Qt::Checked);
    ffmpeg_fps->setEnabled(false);

    connect(ffmpeg_same, SIGNAL(clicked()), this, SLOT(chkStateChanged()));

    ffmpeg_file = new QLabel(tr("Select File Path"), this);
    ffmpeg_file->setGeometry(25,105+25+5, 300, 25);
    ffmpeg_file_set = new QPushButton(tr("Select"), this);
    ffmpeg_file_set->setGeometry(25+310,105+25+5,100,25);

    connect(ffmpeg_file_set, SIGNAL(clicked()), this, SLOT(selectPath()));
}

void RecordWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}

void RecordWindow::saveSettings() {
    // validate form
    // set enabled
    // main_window->enableRecord();
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
