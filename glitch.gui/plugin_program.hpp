
#ifndef _PLUGIN_PROGRAM_H_
#define _PLUGIN_PROGRAM_H_

#include<QLibrary>
#include<unordered_map>
#include<vector>
#include<iostream>

namespace cv {
    class Mat;
}

typedef void (*proc)(cv::Mat &frame);
typedef void (*func)();


class Plugin_Program  {
public:
    Plugin_Program(const QString &filename);
    QLibrary library;
    proc f_proc;
    func f_init;
    func f_clear;
    func f_rls;
    bool init = false;
};

using AC_Plugin = std::pair<std::string, Plugin_Program *>;
void load_plugins(const std::string &path, std::vector<AC_Plugin> &files);
void release_plugins(std::vector<AC_Plugin> &files);
extern std::unordered_map<std::string, int> plug_map;
extern std::vector<AC_Plugin> plugins;
#endif