#ifndef _CUSTOM_EDIT_HPP_
#define _CUSTOM_EDIT_HPP_
#include<QComboBox>
#include<QPushButton>
#include<QDialog>

class MainWindow;

class CustomEditWindow : public QDialog {
Q_OBJECT
public:
    CustomEditWindow(QWidget *parent = 0);
    QComboBox *filter_names;
    QPushButton *filter_rmv;
    void updateFilterNames();
    void setMainWindow(MainWindow *m);
public slots:
    void removeCustom();
private:
    MainWindow *main_window = nullptr;

};



#endif