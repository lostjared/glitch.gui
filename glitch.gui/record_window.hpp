#ifndef RECORD_WINDOW_HPP_
#define RECORD_WINDOW_HPP_

#include<QDialog>
#include<QPushButton>
#include<QLineEdit>
#include<QComboBox>
#include<QCheckBox>
#include<QLabel>

class MainWindow;

struct RecordInfo {
    std::string fps;
    std::string crf;
    std::string filename;
    std::string codec;
    std::string dst;
    std::string src;
    std::string ffmpeg_path;
    bool load_start = false;
    bool save_png = false;
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
public slots:
    void saveSettings();
    void chkStateChanged();
    void selectPath();
    void setPath();
    
private:
    MainWindow *main_window = nullptr;
    QLineEdit *ffmpeg_path;
    QComboBox *ffmpeg_type;
    QPushButton *settings_save;
    QLineEdit *ffmpeg_fps, *ffmpeg_crf;
 
     QLabel *ffmpeg_file;
    QPushButton *ffmpeg_file_set;
    bool path_selected = false;
 };

#endif