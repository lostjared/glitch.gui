#ifndef RECORD_WINDOW_HPP_
#define RECORD_WINDOW_HPP_

#include<QDialog>
#include<QPushButton>
#include<QLineEdit>
#include<QComboBox>

class MainWindow;

class RecordWindow : public QDialog {
    Q_OBJECT
public:
    RecordWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
private:
    MainWindow *main_window;
    QLineEdit *ffmpeg_path;
    QComboBox *ffmpeg_type;
};


#endif