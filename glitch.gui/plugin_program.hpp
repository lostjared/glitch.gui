
#ifndef _PLUGIN_PROGRAM_H_
#define _PLUGIN_PROGRAM_H_

#include"acidcam/ac.h"
#include<QLibrary>

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
};

using AC_Plugin = std::pair<std::string, Plugin_Program *>;
void load_plugins(const std::string &path, std::vector<AC_Plugin> &files);

#endif