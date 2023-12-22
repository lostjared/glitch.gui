#ifndef _MUX_WINDOW_H_
#define _MUX_WINDOW_H_

#include<QDialog>
#include<QLabel>
#include<QPushButton>


class MuxWindow : public QDialog {
Q_OBJECT

public:
    MuxWindow(QWidget *paret = 0);
private:
    QLabel *file_source, *file_copy, *file_dest;
    QPushButton *select_source, *select_copy, *select_dest, *mux_files;
    bool values_set[3] = { false };
public slots:
    void select_Source();
    void select_Copy();
    void select_Dest();
    void mux_Files();
};

#endif