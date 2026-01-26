#include"about_window.hpp"
#include"version_info.hpp"
#include<QTextStream>
#include<QVBoxLayout>

AboutWindow::AboutWindow(QWidget *parent) : QDialog(parent) {
    setMinimumSize(500, 400);
    resize(640, 480);
    QString text;
    QTextStream stream(&text);
    stream << "about glitch.gui v" << APP_VERSION;
    setWindowTitle(text);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    
    view = new QWebEngineView(this);
    view->load(QUrl("https://lostsidedead.biz/glitch.gui/index.html"));
    mainLayout->addWidget(view);
    
    setLayout(mainLayout);
}