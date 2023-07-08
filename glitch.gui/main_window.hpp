#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include<QMainWindow>
#include<QMenu>
#include<QAction>
#include"acidcam/ac.h"

cv::Mat QImage2Mat(QImage const& src);
QImage Mat2QImage(cv::Mat const& src);

class ToolboxWindow;
class DisplayWindow;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    void paintEvent(QPaintEvent *event) override;
private:
    QMenu *file_menu;
    QAction *file_open;
    ToolboxWindow *toolbox_window;
    DisplayWindow *display_window;
    QImage image;
public slots:
    void openFile();


};


#endif