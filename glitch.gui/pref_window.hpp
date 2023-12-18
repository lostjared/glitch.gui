#include<QDialog>
#include<QCheckBox>
#include<QPushButton>
#include<QSettings>

class MainWindow;

class PrefWindow : public QDialog {
    Q_OBJECT
public:
    PrefWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
    QCheckBox *chk_path;
    QPushButton *pref_save, *pref_cancel;
    QSettings settings;
public slots:
    void pref_Save();
    void pref_Cancel();

private:
    MainWindow *main_window;

};