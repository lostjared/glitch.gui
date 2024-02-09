#include"about_window.hpp"
#include"version_info.hpp"
#include<QTextStream>

AboutWindow::AboutWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(640, 480);
    QString text;
    QTextStream stream(&text);
    stream << "about glitch.gui v" << APP_VERSION;
    setWindowTitle(text);
#ifdef _HAS_WEBVIEW_H_
    view = new QWebEngineView(this);
    view->setGeometry(rect());
    view->load(QUrl("https://lostsidedead.biz/glitch.gui/index.html"));
#endif

}