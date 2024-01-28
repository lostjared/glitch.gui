#ifndef _NEW_IMAGE_H_
#define _NEW_IMAGE_H_

#include<QDialog>
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QCheckBox>

class MainWindow;

class NewImageWindow : public QDialog {
    Q_OBJECT
public:
    NewImageWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *main_w);
    bool fileOpen();
    float getFPS(const QString &filename, int &width, int &height);
public slots:
    void openRecordOptions();

private:
    MainWindow *main_window;
    QLabel *input_file;
    QPushButton *input_file_select;
    QLabel *output_location;
    QPushButton *output_location_select;
    QLineEdit *video_fps, *video_filename;
    QPushButton *video_start;
    QCheckBox *video_record;
  
    bool filename_set = false, outdir_set = false;
    
    public slots:
    void openFile();
    void selectDir();
    void videoStart();
};

#endif
