#include"debug_window.hpp"
#include<QIcon>
#include<QTextStream>
#include"version_info.hpp"
// Debug Window constructor - (init)
DebugWindow::DebugWindow(QWidget *parent) : QDialog(parent) {
    setGeometry(10, 600, 1280, 320);
    setFixedSize(1280, 320);
    setWindowFlag(Qt::Tool);
    setWindowTitle(tr("Debug Console"));
    setWindowIcon(QIcon(":/images/icon.png"));
    text_view = new QTextEdit(this);
    text_view->setGeometry(10, 10, 1280-20, 320-20);
    text_view->setReadOnly(true);
    text_view->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255); font-size: 20px;");
    QString text;
    QTextStream stream(&text);
    stream << "gui: glitch.gui v" << APP_VERSION << " Loaded\n";
    stream << "gui: " << APP_YEAR << " LostSideDead Software\n";
    Log(text);
    //setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}

// clear the debug window
void DebugWindow::clear() {
    text_view->setHtml("");
}
// add Log message to debug window
void DebugWindow::Log(const QString &text) {
    QString current;
    current = text_view->toPlainText();
    current += text;
    current.replace("gui: ", "<span style=\"color: red;\">gui: </span>");
    current.replace("glitch: ", "<span style=\"color: green;\">glitch: </span>");
    current.replace("\n", "<br>");
    text_view->setHtml(current);
    QTextCursor tmpCursor = text_view->textCursor();
    tmpCursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    text_view->setTextCursor(tmpCursor);
}
