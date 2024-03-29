#ifndef _TOOLBOX_WINDOW_H_
#define _TOOLBOX_WINDOW_H_

#include<QDialog>
#include<QPushButton>
#include<QLabel>
#include<QCheckBox>
#include"acidcam/ac.h"

class DisplayWindow;
class RecordWindow;
class MainWindow;

class ToolboxWindow : public QDialog {
    Q_OBJECT
public:
    ToolboxWindow(QWidget *parent = 0);
    void setOutputDirectory(const QString &odir, const QString &prefix);
    void setDisplayWindow(DisplayWindow *disp);
    void setRecordWindow(RecordWindow *r);
    void setMainWindow(MainWindow *m);
    void enableButtons();
    void disableButtons();
    void enableSource();
    void disableSource();
    void setHide();
    void setShow();
    void setRecordText(bool b);
    void setStopText();
    void setStartText();
    void enableRecord();
public slots:
    void saveSnapshot();
    void setSource();
    void stopAction();
    void stepAction();
    void selectColor();
    void clickOffset(bool);
    void clickFade(bool);
    void showDisplay();
    void showRecord();
    void recordNow();
private:
    QLabel *color_lbl;
    QString outdir;
    DisplayWindow *display_window = nullptr;
    RecordWindow *record_window = nullptr;
    MainWindow *main_window = nullptr;
    int snap_index = 0;
    QPushButton *save_snapshot, *setsource_action, *stop_action, *step_action, *sel_color, *show_disp, *record_btn, *record_now;
    QCheckBox *use_color, *use_fade;
    cv::Vec3b color_value;
    QString prefix;
};

#endif
