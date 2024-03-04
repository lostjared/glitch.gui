#ifndef _CUSTOM_WINDOW_H_
#define _CUSTOM_WINDOW_H_

#include<QDialog>
#include<QComboBox>
#include<QListWidget>
#include<QLineEdit>
#include<QCheckBox>

class MainWindow;

class CustomWindow : public QDialog {
    Q_OBJECT
public:
    CustomWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
    void loadCategory(int cat);
    bool createCustom(const QString &name); 
    void addItem(const QString &text);
    QString getRGB();
public slots:
    void addFilter();
    void rmvFilter();
    void move_Up();
    void move_Down();
    void changeCategory(int cat);
    void changeCustom(int custom);
    void setFilter();
    void updateFilter();
    void setPlaylist();
private:
    MainWindow *main_window = nullptr;
    QComboBox *filter, *filter_cat, *filter_name_combo;
    QListWidget *filter_custom;
    QLineEdit *filter_name;
    QPushButton *btn_add, *btn_rmv, *btn_up, *btn_down, *btn_set, *btn_playlist, *btn_update;
    QCheckBox *chk_r, *chk_g, *chk_b;
};

#endif