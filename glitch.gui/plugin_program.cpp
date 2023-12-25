
#include"plugin_program.hpp"

Plugin_Program::Plugin_Program(const QString &filename) : library(filename) {
    f_init = (func) library.resolve("init");
    f_rls = (func) library.resolve("rls");
    f_proc = (proc) library.resolve("proc");
    f_clear = (func) library.resolve("clear");

    if(f_init == 0 || f_rls == 0 || f_proc == 0 || f_clear == 0) {
        std::cerr << "fatal error plugin missing function..\n";
        exit(EXIT_FAILURE);
    }
}
