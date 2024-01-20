#include<QApplication>
#include"main_window.hpp"
#include"pref_window.hpp"
#include"cat_vec.hpp"
#include<ctime>
#include<cstdlib>
#ifdef _WIN32
#include<windows.h>
#endif

QSettings settings("LostSideDead", "glitch.gui");

int main(int argc, char **argv) {
#ifdef _WIN32
    HANDLE hInput;
    DWORD prev_mode;
    hInput = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hInput, &prev_mode); 
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
#endif
    QApplication app(argc, argv);
    // init random seed
    srand(static_cast<unsigned int>(time(0)));
    std::cout << APP_NAME << " v" << APP_VERSION << "\n";
    std::cout << APP_YEAR << " LostSideDead Software. GPL v3.\n";
    ac::init();
    ac::setMaxAllocated(325);
    std::cout << "libacidcam v" << ac::version << " succesfully loaded...\n";
    QString fname = settings.value("chk_filename").toString();
    if(fname != "")
        build_lists(fname.toStdString());

    MainWindow main_window;
    main_window.show();
    app.exec();
#ifdef _WIN32
    SetConsoleMode(hInput, prev_mode);
#endif
    return 0;
}