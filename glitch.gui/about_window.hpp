#ifndef __ABOUT_WINDOW_H__
#define __ABOUT_WINDOW_H__

#include<QDialog>
#include<QTextEdit>
#include<QLabel>
#include<QPushButton>
//#define _HAS_WEBVIEW_H_
#ifdef _HAS_WEBVIEW_H_
#include <QtWebEngineWidgets>
#endif
class AboutWindow : public QDialog {
    Q_OBJECT
public:
    AboutWindow(QWidget *parent = 0);

protected:
    QTextEdit *edit;
    QLabel *lbl;
    QPushButton *btn_ok;
#ifdef _HAS_WEBVIEW_H_
    QWebEngineView *view;
#endif
};


#endif