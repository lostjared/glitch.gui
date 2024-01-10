#ifndef _PREF_WINDOW_H_
#define _PREF_WINDOW_H_

#include<QDialog>
#include<QCheckBox>
#include<QPushButton>
#include<QSettings>
#include<QLabel>
#include<QLineEdit>

class MainWindow;

class PrefWindow : public QDialog {
    Q_OBJECT
public:
    PrefWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
    QCheckBox *chk_path;
    QPushButton *pref_save, *pref_cancel, *pref_custom;
    QSettings settings;
    QLabel *custom_path_lbl;
    bool savePath() const;
    QString custom_path;

public slots:
    void pref_Save();
    void pref_Cancel();
    void pref_setPath();

private:
    MainWindow *main_window;

};

#endif