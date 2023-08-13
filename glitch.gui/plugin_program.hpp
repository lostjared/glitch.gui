
#ifndef _PLUGIN_PROGRAM_H_
#define _PLUGIN_PROGRAM_H_

#include"acidcam/ac.h"


class Plugin_Program {
public:
    Plugin_Program(const std::string &filename);
    void (*init)() = 0;
    void (*clear)() = 0;
    void (*proc)(cv::Mat &frame) = 0;
    void (*free)() = 0;
};


#endif