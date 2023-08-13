
#ifndef _PLUGIN_PROGRAM_H_
#define _PLUGIN_PROGRAM_H_

#include"acidcam/ac.h"
#include<QLibrary>

typedef void (*proc)(cv::Mat &frame);
typedef void (*init)();
typedef void (*clear)();
typedef void (*rls)();

class Plugin_Program  {
public:
    Plugin_Program(const QString &filename);
    QLibrary library;
    proc f_proc;
    init f_init;
    clear f_clear;
    rls f_rls;
};

#endif