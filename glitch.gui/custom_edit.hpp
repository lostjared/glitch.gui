#ifndef _CUSTOM_EDIT_HPP_
#define _CUSTOM_EDIT_HPP_
#include<QComboBox>
I#iclude<QPushButton>
#include<QDialog>

class CustomEditWindow : public QDialog {
public:
    CustomEditWindow(QWidget *parent = 0);
    QComboBox *filer_names;
    QPushButton *rmv;

    void updateFilterNames();

};



#endif