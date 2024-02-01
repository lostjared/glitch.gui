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
#include<cstdio>
#include<QTextStream>
#include<QProgressBar>
#include"plugin_program.hpp"
#include"acidcam/ac.h"

cv::Mat QImage2Mat(QImage const& src);
QImage Mat2QImage(cv::Mat const& src);

class ToolboxWindow;
class DisplayWindow;
class NewImageWindow;
class DebugWindow;
class RecordWindow;
class CustomWindow;
class CustomEditWindow;
class PrefWindow;
class MuxWindow;
class Control_Window;
class RotateWindow;
class LayersWindow;

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    MainWindow();
    ~MainWindow();
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyShiftUp();
    void keyShiftDown();
    void startNewAnimation(const QString &filename, const QString &outdir, const QString &prefix, float fps);
    void loadCategory(int index);
    void disableUndo();
    void enableUndo();
    void setInfo(const cv::Mat &frame);
    void enableRecord();
    bool startRecording(const QString &filename, const QString &codec_type, const QString &dst_res, const QString &crf, const QString &fps);
    void record();
    void writeFrame(cv::Mat &frame);
    bool isFileOpen();
    void setAniString(const QString &ani);
    void setMinMax(int min, int max);
    void setImageDelay(int delay);
    void initPlaylist();
    DebugWindow *debug_window;
    ToolboxWindow *toolbox_window;
    RecordWindow *record_window;
    DisplayWindow *display_window;
    NewImageWindow *newimage_window;
    CustomWindow *custom_window;
    CustomEditWindow *custom_edit;
    PrefWindow *pref_window;
    MuxWindow *mux_window;
    Control_Window *control_window;
    RotateWindow *rotate_window;
    LayersWindow *layers_window;
    int current_width = 0, current_height = 0; 
private:
    QMenu *file_menu, *edit_menu, *record_menu, *image_menu, *filter_menu,*tools_menu, *help_menu, *audio_menu;
    QAction *file_open, *file_pref, *file_exit;
    QAction *edit_undo, *edit_redo;
    QAction *record_set, *record_rec, *record_repeat, *record_control, *record_reset, *record_layers;
    QAction *image_save, *image_step, *image_set_source, *image_ani;
    QAction *filter_custom, *filter_edit, *filter_menu_release, *filter_playlist_open, *filter_playlist_clear;
    QAction *rotate_item;
    QAction *audio_mux;

    QAction *help_about; 
    QImage image;
    QComboBox *filter_list, *filter_cat;
    QListWidget *filter_list_view;
    QLineEdit *filter_search;
    QPushButton *filter_search_button, *filter_search_set, *filter_first_set, *filter_first_clear, *filter_set_custom, *filter_add_custom, *filter_release, *filter_btn_exit;
    QLabel *filter_first;
    QTextEdit *content_data;
    std::string first_filter = "None";
    std::string cur_filename;
    FILE *file_stream = NULL;
    QProgressBar *bar_position;
    int video_speed = 1;
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
    void showRecord();
    void recordVideo();
    QString contentData(const std::string &fn, const cv::Mat &frame);
    void toggle_repeat();
    void stopRecording();
    void image_Save();
    void image_Step();
    void image_Set();
    void image_Ani();
    void filter_Show();
    void filter_Edit();
    void custom_Add();
    void file_Pref();
    void menu_Audio();
    void custom_filter_add();
    void showControls();
    void filterRelease();
    void quitProgram();
    void showRotateWindow();
    void recordReset();
    void playlistOpen();
    void playlistClear();
    void recordLayers();
};


#endif
