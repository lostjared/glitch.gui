#ifndef _DISP_WINDOW_H_
#define _DISP_WINDOW_H_

#include<QDialog>
#include<QPaintEvent>
#include<QLabel>
#include<QTimer>
#include<deque>
#include"acidcam/ac.h"

class DebugWindow;
class MainWindow;

enum class InputMode { IMAGE, VIDEO };

class DisplayWindow : public QDialog {
    Q_OBJECT
public:
    DisplayWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
    void setDebugWindow(DebugWindow *d);    
    void setSourceImage(const cv::Mat &src);
    void paintEvent(QPaintEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;

    void display(QImage &image);
    void display(const cv::Mat &src);

    void startAnimation();
    void startAnimation(float fps);
    void stopAnimation();
    void setCurrentFilter(const std::string &f);

    void takeSnapshot(const QString &text, const QString &file_type);
    void setSource();

    void step();
    void setPrefix(const QString &dir, const QString &p);
    void setColorOffset(const cv::Vec3b &color);
    void setFilterFirst(const std::string &first);
    void undo();
    void redo();

    void resetInputMode(const InputMode &m, std::string source_file);

public slots:
    void timeoutFunc();


private:
    cv::Mat source_image, image;
    QLabel *image_label;
    QTimer *timer; 
    std::string current_filter;
    DebugWindow *debug_window = nullptr;
    MainWindow *main_window = nullptr;
    float fps = 24.0;
    cv::Vec3b color_offset;
    std::string first_filter;
    QString outdir, prefix;
    std::deque<cv::Mat> undo_list;
    std::deque<cv::Mat> redo_list;
    void setColorOffset(cv::Mat &frame);
    InputMode mode = InputMode::IMAGE;
    cv::VideoCapture cap;
};

#endif