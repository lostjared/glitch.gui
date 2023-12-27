#include<QApplication>
#include"main_window.hpp"
#include<ctime>
#include<cstdlib>


int main(int argc, char **argv) {
    QApplication app(argc, argv);
    // init random seed
    srand(static_cast<unsigned int>(time(0)));
    std::cout << APP_NAME << " v" << APP_VERSION << "\n";
    std::cout << "(C) 2024 LostSideDead Software. GPL v3.\n";
    MainWindow main_window;
    main_window.show();
    app.exec();
    return 0;
}
