#include"acidcam/ac.h"


extern "C" void init() {
    std::cout << "plugin initialized..\n";
}

extern "C" void rls() {
    std::cout << "plugin released..\n";
}

extern "C" void clear() {
    std::cout << "Clear called..\n";
}

extern "C" void proc(cv::Mat &frame) {
    std::cout << "process here..\n";   
}