#ifndef __ABOUT_WINDOW_H__
#define __ABOUT_WINDOW_H__

#include<QDialog>
#include<QTextEdit>
#include<QLabel>
#include<QPushButton>
#include <QWebEngineView>

class AboutWindow : public QDialog {
    Q_OBJECT
public:
    AboutWindow(QWidget *parent = 0);

protected:
    QTextEdit *edit;
    QLabel *lbl;
    QPushButton *btn_ok;
    QWebEngineView *view;
};


#endif