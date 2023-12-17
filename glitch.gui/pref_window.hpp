#include<QDialog>
#include<QCheckBox>

class MainWindow;

class PrefWindow : public QDialog {
    Q_OBJECT
public:
    PrefWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
    QCheckBox *chk_path;
private:
    MainWindow *main_window;

};