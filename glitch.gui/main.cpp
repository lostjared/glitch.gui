#include<QApplication>
#include"main_window.hpp"


int main(int argc, char **argv) {
    QApplication app(argc, argv);
    std::cout << APP_NAME << " v" << APP_VERSION << "\n";
    MainWindow main_window;
    main_window.show();
    app.exec();
    return 0;
}