#ifndef _NEW_IMAGE_H_
#define _NEW_IMAGE_H_

#include<QDialog>
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QCheckBox>
#include<QScrollBar>

class MainWindow;

class NewImageWindow : public QDialog {
    Q_OBJECT
public:
    NewImageWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *main_w);
    bool fileOpen();
    float getFPS(const QString &filename, int &width, int &height);
    void enableStart(bool b);
public slots:
    void openRecordOptions();
    void changedPos(int value);
private:
    MainWindow *main_window;
    QLabel *input_file;
    QPushButton *input_file_select;
    QLabel *output_location;
    QPushButton *output_location_select;
    QLineEdit *video_fps, *video_filename;
    QPushButton *video_start;
    QCheckBox *video_record;
    QScrollBar *video_image_delay;  
    bool filename_set = false, outdir_set = false;
    QLabel *num_label;
public slots:
    void openFile();
    void selectDir();
    void videoStart();
};

#endif
