#include"new_image.hpp"
#include"main_window.hpp"
#include"record_window.hpp"
#include"pref_window.hpp"
#include"debug_window.hpp"
#include<QFileDialog>
#include<QIcon>
#include<QMessageBox>
#include<QTextStream>

NewImageWindow::NewImageWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Start new Animation");
    setWindowIcon(QIcon(":/images/icon.png"));
    setFixedSize(320, 240);
    input_file = new QLabel(tr("Select File Location"), this);
    input_file->setGeometry(10, 10, 240, 25);
    input_file_select = new QPushButton("...", this);
    input_file_select->setGeometry(260, 10, 50, 25);
    connect(input_file_select, SIGNAL(clicked()), this, SLOT(openFile()));
    output_location = new QLabel(tr("Select Output Location"), this);
    output_location->setGeometry(10, 35, 240, 25);
    output_location_select = new QPushButton("...", this);
    output_location_select->setGeometry(260, 35, 50, 25);
    connect(output_location_select, SIGNAL(clicked()), this, SLOT(selectDir()));
    QLabel *cap = new QLabel(tr("FPS"), this);
    cap->setGeometry(10, 75, 50, 25);
    video_fps = new QLineEdit("24", this);
    video_fps->setGeometry(65, 75, 100, 25);
    video_start = new QPushButton(tr("Start"), this);
    video_start->setGeometry(320-100-10, 240-35, 100, 30);   
    connect(video_start, SIGNAL(clicked()), this, SLOT(videoStart())); 
    video_start->setEnabled(false);
    filename_set = false;
    outdir_set = false;
    QLabel *prefix = new QLabel(tr("Filename Prefix:"), this);
    prefix->setGeometry(10, 110, 100, 30);
    video_filename = new QLineEdit(this);
    video_filename->setText(tr("Glitch1"));
    video_filename->setGeometry(110, 110, 195, 30);
    video_record = new QCheckBox(tr("Record on Start"), this);
    video_record->setGeometry(10, 140, 150, 25);
    video_record->setChecked(Qt::Unchecked);
    video_image_delay = new QScrollBar(Qt::Horizontal, this);
    num_label = new QLabel("Image Delay: 1", this);
    num_label->setGeometry(10, 172, 100, 25);
    video_image_delay->setGeometry(110, 170, 200, 25);
    video_image_delay->setMinimum(1);
    video_image_delay->setMaximum(10);
    video_image_delay->setValue(1);

    video_image_delay->setEnabled(false);

    connect(video_record, SIGNAL(clicked()), this, SLOT(openRecordOptions()));
    connect(video_image_delay, SIGNAL(valueChanged(int)), this, SLOT(changedPos(int)));
    //setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

}

void NewImageWindow::changedPos(int) {
    QString text;
    QTextStream stream(&text);
    stream << "Image Delay: " << video_image_delay->value();
    num_label->setText(text);
}

void NewImageWindow::setMainWindow(MainWindow *main_w) {
    main_window = main_w;
}

void NewImageWindow::openFile() {
    QString filename;
    QString path;
    auto lwr = [](const QString &text) -> std::string {
        std::string t;
        std::string text1{text.toStdString()};
        for(std::string::size_type i = 0; i < text1.length(); ++i) {
            t += tolower(text1[i]);
        }
        return t;;
    };

    if(main_window->pref_window->savePath())
        path = settings.value("image_file_path").toString();

    filename = QFileDialog::getOpenFileName(this,tr("Open Image/Video"), path, tr("Image/Video Files (*.png *.jpg *.bmp *.avi *.mov *.mp4 *.mkv)"));
    if(filename != "") {
        std::string lwr_chkd = lwr(filename);
        if(lwr_chkd.find(".png") != std::string::npos || lwr_chkd.find(".jpg") != std::string::npos || lwr_chkd.find(".bmp") != std::string::npos) {
            video_image_delay->setEnabled(true);
        } else {
            video_image_delay->setEnabled(false);
        }
        input_file->setText(filename);
        QString text;
        QTextStream stream(&text);
        int width = 0, height = 0;
        stream << getFPS(filename, width, height);
        main_window->current_width = width;
        main_window->current_height = height;
        if(main_window->record_window->ffmpeg_same->isChecked())
            main_window->record_window->fps_same = text;
        filename_set = true;
        if(outdir_set == true && filename_set == true) {
            video_start->setEnabled(true);
        }
        if(main_window->pref_window->savePath())
            settings.setValue("image_file_path", filename);
    }
}

void NewImageWindow::selectDir() {
    QString dir;
    QString path;

    if(main_window->pref_window->savePath())
        path = settings.value("image_path").toString();


    dir = QFileDialog::getExistingDirectory(this, tr("Open Dir"), path);
    if(dir != "") {
        output_location->setText(dir);
        outdir_set = true;
        if(outdir_set == true && filename_set == true) {
            video_start->setEnabled(true);
        }
        if(main_window->pref_window->savePath())
            settings.setValue("image_path", dir);
    }
    
}

void NewImageWindow::videoStart() {
    float fps = video_fps->text().toFloat();
    QString prefix = video_filename->text();
    
    if(fps > 0 && prefix.length() > 0 && filename_set == true && outdir_set == true) {
        QString filename = input_file->text();
        QString outdir = output_location->text();

        if(video_record->checkState() == Qt::Checked) {
            if(main_window->record_window->ready() == false) {
                QMessageBox msgbox;    
                msgbox.setWindowTitle(tr("Record Info not set"));
                msgbox.setIcon(QMessageBox::Icon::Critical);
                msgbox.setWindowIcon(QIcon(":/images/icon.png"));
                msgbox.setText(tr("You must select path for outputted videos click Select and choose a directory.\n"));
                msgbox.exec();
                return;
            }
        }

        if(video_record->checkState() == Qt::Checked)
            main_window->record_window->rec_info.load_start = true;
        else
            main_window->record_window->rec_info.load_start = false;


        main_window->setImageDelay(video_image_delay->value());

        QString msg;
        QTextStream stream(&msg);
        if(video_image_delay->isEnabled()) {
            stream << "gui: Set IMAGE Mode Video Delay to: " << video_image_delay->value() << "\n";
            main_window->debug_window->Log(msg);
        } else {
            main_window->setImageDelay(1);
            main_window->debug_window->Log("gui: In Video Mode IMAGE Delay disabled.\n");   
        }
        main_window->startNewAnimation(filename, outdir, prefix, fps);
        hide();
    } else {
        QMessageBox box;
        box.setWindowTitle("Error invalid input information");
        box.setText("Invalid input information fill out form correctly");
        box.setIcon(QMessageBox::Icon::Warning);
        box.exec();
    }
}

void NewImageWindow::openRecordOptions() {
    if(video_record->checkState() == Qt::Checked) 
        main_window->record_window->show();
}

float NewImageWindow::getFPS(const QString &filename, int &width, int &height) {
    cv::VideoCapture cap;
    cap.open(filename.toStdString());
    if(cap.isOpened()) {
        width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
        height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
        return static_cast<float>(cap.get(cv::CAP_PROP_FPS));
    }
    cv::Mat test_img = cv::imread(filename.toStdString());
    if(test_img.empty()) {
        width = test_img.cols;
        height = test_img.rows;
    }  
    return 24.0f;
}