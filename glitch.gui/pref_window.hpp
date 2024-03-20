#ifndef _PREF_WINDOW_H_
#define _PREF_WINDOW_H_

#include<QDialog>
#include<QCheckBox>
#include<QPushButton>
#include<QSettings>
#include<QLabel>
#include<QLineEdit>

class MainWindow;

extern QSettings settings;

class PrefWindow : public QDialog {
    Q_OBJECT
public:
    PrefWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
    QCheckBox *chk_path;
    QPushButton *pref_save, *pref_cancel, *pref_custom;
    QLabel *custom_path_lbl;
    bool savePath() const;
    QString custom_path;
    bool loaded = false;
public slots:
    void pref_Save();
    void pref_Cancel();
    void pref_setPath();
    void grab_color1();
    void grab_color2();
   
private:
    MainWindow *main_window;
    QLineEdit *frac_real, *frac_imag, *frac_zoom, *frac_iter, *frac_speed, *frac_max;
    QLabel *color_start, *color_stop;
    QPushButton *color_start_btn, *color_stop_btn;
};

#endif