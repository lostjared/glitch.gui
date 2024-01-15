
#include"plugin_program.hpp"
#include<filesystem>

std::unordered_map<std::string, int> plug_map;
std::vector<AC_Plugin> plugins;

Plugin_Program::Plugin_Program(const QString &filename) : library(filename) {
    f_init = (func) library.resolve("init");
    f_rls = (func) library.resolve("rls");
    f_proc = (proc) library.resolve("proc");
    f_clear = (func) library.resolve("clear");

    if(f_init == 0 || f_rls == 0 || f_proc == 0 || f_clear == 0) {
        std::cerr << "error plugin: " << filename.toStdString() << " missing function..\n";
//        exit(EXIT_FAILURE);
    }
}

void load_plugins(const std::string &path, std::vector<AC_Plugin> &files) {
    std::cout << "Loading plugins from path: " << path << "\n";
    std::filesystem::path p{path};
    if(is_directory(p)) {
        for(auto &i : std::filesystem::recursive_directory_iterator(path)) {
            std::string f = i.path().string();
            if(f.find(".acidcam") != std::string::npos) {
                std::cout << "Loading: " << f << "\n";
                files.push_back(std::make_pair(f, new Plugin_Program(f.c_str())));
            }
        }
    } else {
        std::cerr << "invalid input..\n";
    }
    for(size_t i = 0; i < files.size(); ++i) {
        plug_map[files[i].first] = i;
    }
    std::cout << "Sucessfully loaded " << files.size() << " plugin(s).\n";
}

void release_plugins(std::vector<AC_Plugin> &files) {
    for(size_t i = 0; i < files.size(); ++i) {
        std::string &f = files[i].first;
        Plugin_Program *prog = files[i].second;
        std::cout << "Releasing: " << f << "\n";
        prog->f_rls();
        delete prog;
    }
}
