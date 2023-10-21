#include"record_window.hpp"
#include"main_window.hpp"

RecordWindow::RecordWindow(QWidget *parent) : QDialog(parent) {
    setGeometry(1200, 100, 640, 480);
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
    settings_save->setGeometry(width()-125,height()-40, 100, 25);

    connect(settings_save, SIGNAL(clicked()), this, SLOT(saveSettings()));
}

void RecordWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}

void RecordWindow::saveSettings() {
    hide();
}