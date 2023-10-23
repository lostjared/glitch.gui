#ifndef RECORD_WINDOW_HPP_
#define RECORD_WINDOW_HPP_

#include<QDialog>
#include<QPushButton>
#include<QLineEdit>
#include<QComboBox>
#include<QCheckBox>

class MainWindow;

class RecordWindow : public QDialog {
    Q_OBJECT
public:
    RecordWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
public slots:
    void saveSettings();
    void chkStateChanged();
    
private:
    MainWindow *main_window;
    QLineEdit *ffmpeg_path;
    QComboBox *ffmpeg_type;
    QPushButton *settings_save;
    QLineEdit *ffmpeg_fps;
    QCheckBox *ffmpeg_same;
};


#endif