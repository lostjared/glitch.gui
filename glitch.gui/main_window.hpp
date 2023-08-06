#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_
#include"version_info.hpp"
#include<QMainWindow>
#include<QMenu>
#include<QAction>
#include<QComboBox>
#include<QListWidget>
#include<QLineEdit>
#include<QTextEdit>
#include<QPushButton>
#include<QLabel>
#include<QKeyEvent>

#include"acidcam/ac.h"

cv::Mat QImage2Mat(QImage const& src);
QImage Mat2QImage(cv::Mat const& src);

class ToolboxWindow;
class DisplayWindow;
class NewImageWindow;
class DebugWindow;

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    MainWindow();
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyShiftUp();
    void keyShiftDown();
    void startNewAnimation(const QString &filename, const QString &outdir, const QString &prefix, float fps);
    void loadCategory(int index);
    void disableUndo();
    void enableUndo();
    DebugWindow *debug_window;
    ToolboxWindow *toolbox_window;
private:
    QMenu *file_menu, *edit_menu, *help_menu;
    QAction *file_open;
    QAction *edit_undo, *edit_redo;
    QAction *help_about; 
    DisplayWindow *display_window;
    NewImageWindow *newimage_window;
    QImage image;
    QComboBox *filter_list, *filter_cat;
    QListWidget *filter_list_view;
    QLineEdit *filter_search;
    QPushButton *filter_search_button, *filter_search_set, *filter_first_set, *filter_first_clear;
    QLabel *filter_first;
    QTextEdit *content_data;
    std::string first_filter = "None";
    public slots:
    void openFile();
    void indexChanged(int index);
    void catIndexChanged(int index);
    void searchFilter();
    void setSearch();
    void helpAbout();
    void firstSet();
    void firstClear();
    void editUndo();
    void editRedo();
};


#endif
