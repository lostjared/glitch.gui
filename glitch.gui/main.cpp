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
std::string current_path;

// RAII 
class ScopedConsoleSettings {
public:
    ScopedConsoleSettings() {
        std::cout << "Setting Console Mode Setings...\n";
#ifdef _WIN32
        hInput = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(hInput, &prev_mode); 
        SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
#endif
    }
    ~ScopedConsoleSettings() {
        std::cout << "Restoring Console Settings...\n";
#ifdef _WIN32
        SetConsoleMode(hInput, prev_mode);
#endif
    }
private:
#ifdef _WIN32
    HANDLE hInput; // resources
    DWORD prev_mode;  
#endif
};


int main(int argc, char **argv) {
#ifdef __APPLE__
    current_path = argv[0];
    current_path = current_path.substr(0, current_path.rfind("/"));
    current_path += "/../Resources/";
#endif
    QApplication app(argc, argv);
    // init random seed
    srand(static_cast<unsigned int>(time(0)));
    std::cout << APP_NAME << " v" << APP_VERSION << "\n";
    std::cout << APP_YEAR << " LostSideDead Software. GPL v3.\nLoading...\n";
    ScopedConsoleSettings scopedConsoleMode;
    ac::init();
    ac::setMaxAllocated(325);
    std::cout << "libacidcam v" << ac::version << " succesfully loaded...\n";
    QString fname = settings.value("chk_filename").toString();
    build_lists(fname.toStdString());
    MainWindow main_window;
    main_window.show();
    app.exec();
    std::cout << "glitch-gui: Shutdown Successful...\n";
   return 0;
}