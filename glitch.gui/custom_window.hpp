#ifndef _CUSTOM_WINDOW_H_
#define _CUSTOM_WINDOW_H_

#include<QDialog>

class CustomWindow : public QDialog {
    Q_OBJECT

public:
    CustomWindow(QWidget *parent = 0);

};

#endif