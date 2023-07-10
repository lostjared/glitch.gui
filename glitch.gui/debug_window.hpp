#ifndef _DEBUG_WINDOW_H_
#define _DEBUG_WINDOW_H_


#include<QDialog>
#include<QTextEdit>

class DebugWindow : public QDialog {
    Q_OBJECT
public:
    DebugWindow(QWidget *parent = 0);
    void Log(const QString &text);
    void clear();
protected:
    QTextEdit *text_view;
};


#endif