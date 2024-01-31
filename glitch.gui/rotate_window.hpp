#ifndef __ROTATE_WINDOW_H__
#define __ROTATE_WINDOW_H__

#include<QDialog>
#include<QLabel>
#include<QPushButton>
#include<QComboBox>

class RotateWindow : public QDialog {
Q_OBJECT
public:
    RotateWindow(QWidget *parent = 0);
private:
    QLabel *item_src, *item_out;
    QPushButton *src_select, *item_select, *btn_rotate;
    bool value_set[2] = {false};
    QComboBox *deg_rotate;
public slots:
    void selectSrc();
    void selectDst();
    void rotateVideo();
};

#endif