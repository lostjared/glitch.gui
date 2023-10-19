#include"record_window.hpp"
#include"main_window.hpp"

RecordWindow::RecordWindow(QWidget *parent) : QDialog(parent) {
   setGeometry(1200, 100, 640, 480);
   setWindowTitle(tr("Record Options"));
}

void RecordWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}