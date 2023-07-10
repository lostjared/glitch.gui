#ifndef _NEW_IMAGE_H_
#define _NEW_IMAGE_H_

#include<QDialog>
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>

class MainWindow;

class NewImageWindow : public QDialog {
    Q_OBJECT
public:
    NewImageWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *main_w);
private:
    MainWindow *main_window;
    QLabel *input_file;
    QPushButton *input_file_select;
    QLabel *output_location;
    QPushButton *output_location_select;
    QLineEdit *video_fps;
    QPushButton *video_start;

public slots:
    void openFile();
    void selectDir();
};

#endif