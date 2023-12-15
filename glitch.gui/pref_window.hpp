#include<QDialog>

class MainWindow;

class PrefWindow : public QDialog {
    Q_OBJECT
public:
    PrefWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
private:
    MainWindow *main_window;

};