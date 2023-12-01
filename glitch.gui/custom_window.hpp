#ifndef _CUSTOM_WINDOW_H_
#define _CUSTOM_WINDOW_H_

#include<QDialog>
#include<QComboBox>
#include<QListWidget>
#include<QLineEdit>

class MainWindow;

class CustomWindow : public QDialog {
    Q_OBJECT
public:
    CustomWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
   
public slots:
    void addFilter();
    void rmvFilter();
    void move_Up();
    void move_Down();
    void changeCategory(int cat);
    void setFilter();

private:
    MainWindow *main_window = nullptr;
    QComboBox *filter, *filter_cat;
    QListWidget *filter_custom;
    QLineEdit *filter_name;
    QPushButton *btn_add, *btn_rmv, *btn_up, *btn_down, *btn_set;
};

#endif