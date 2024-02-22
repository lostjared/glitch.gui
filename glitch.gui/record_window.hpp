#ifndef RECORD_WINDOW_HPP_
#define RECORD_WINDOW_HPP_

#include<QDialog>
#include<QPushButton>
#include<QLineEdit>
#include<QComboBox>
#include<QCheckBox>
#include<QLabel>
#include<QCheckBox>

class MainWindow;

struct RecordInfo {
    std::string fps;
    std::string crf;
    std::string filename;
    std::string codec;
    std::string dst;
    std::string src;
    std::string ffmpeg_path;
    std::string stretch_dst;
    bool load_start = false;
    bool save_png = false;
    bool stretch = false;
    int stretch_width = 0;
    int stretch_height = 0;
};

class RecordWindow : public QDialog {
    Q_OBJECT
public:
    RecordWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
    QCheckBox *ffmpeg_same, *ffmpeg_man; 
    RecordInfo rec_info;
    bool rec_info_set = false;
    QString fps_same;

    bool ready();

public slots:
    void saveSettings();
    void chkStateChanged();
    void selectPath();
    void setPath();
    void stateChecked();

private:
    MainWindow *main_window = nullptr;
    QLineEdit *ffmpeg_path;
    QCheckBox *stretch_video;
    QLineEdit *stretch_width, *stretch_height;
    QComboBox *ffmpeg_type;
    QPushButton *settings_save;
    QLineEdit *ffmpeg_fps, *ffmpeg_crf;
 
     QLabel *ffmpeg_file;
    QPushButton *ffmpeg_file_set;
    bool path_selected = false;
 };

#endif