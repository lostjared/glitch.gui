#include"pref_window.hpp"
#include"debug_window.hpp"
#include"main_window.hpp"

PrefWindow::PrefWindow(QWidget *parent) : QDialog(parent), settings("LostSideDead", "glitch.gui") {
    setFixedSize(640, 480);
    setWindowTitle("Preferences");

    chk_path = new QCheckBox(tr("Save Directory Paths"), this);
    chk_path->setGeometry(25,25,200,25);

    pref_save = new QPushButton(tr("Save"), this);
    pref_save->setGeometry(25,height()-40,75,25);

    pref_cancel = new QPushButton(tr("Cancel"), this);
    pref_cancel->setGeometry(120, height()-40, 75, 25);

    connect(pref_save, SIGNAL(clicked()), this, SLOT(pref_Save()));
    connect(pref_cancel, SIGNAL(clicked()), this, SLOT(pref_Cancel()));

    chk_path->setChecked(settings.value("chk_path").toBool());
}

void PrefWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}

void PrefWindow::pref_Save() {
    settings.setValue("chk_path", chk_path->isChecked());   
    hide(); 
    main_window->debug_window->Log("gui: Preferences saved.\n");
}

void PrefWindow::pref_Cancel() {
    hide();
}

bool PrefWindow::savePath() const {
    return chk_path->isChecked();
}