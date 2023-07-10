#ifndef _TOOLBOX_WINDOW_H_
#define _TOOLBOX_WINDOW_H_

#include<QDialog>
#include<QPushButton>

class DisplayWindow;


class ToolboxWindow : public QDialog {
    Q_OBJECT
public:
    ToolboxWindow(QWidget *parent = 0);
    void setOutputDirectory(const QString &odir);
    void setDisplayWindow(DisplayWindow *disp);
public slots:
    void saveSnapshot();

private:
    QString outdir;
    DisplayWindow *display_window;
    int snap_index = 0;
    QPushButton *save_snapshot;

};

#endif