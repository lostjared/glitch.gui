#ifndef _CUSTOM_WINDOW_H_
#define _CUSTOM_WINDOW_H_

#include<QDialog>
#include<QComboBox>
#include<QListView>
#include<QLineEdit>

class MainWindow;

class CustomWindow : public QDialog {
    Q_OBJECT
public:
    CustomWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
private:
    MainWindow *main_window = nullptr;
    QComboBox *filter, *filter_cat;
    QListView *filter_custom;
    QLineEdit *filter_name;
};

#endif