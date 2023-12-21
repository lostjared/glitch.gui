#ifndef _MUX_WINDOW_H_
#define _MUX_WINDOW_H_

#include<QDialog>


class MuxWindow : public QDialog {
Q_OBJECT

public:
    MuxWindow(QWidget *paret = 0);
};

#endif