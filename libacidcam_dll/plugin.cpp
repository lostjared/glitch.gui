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
    for(int z = 0; z < frame.rows; ++z) {
        for(int i = 0; i < frame.cols; ++i) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            pixel = cv::Vec3b(0, 0, 0);
        }
    }
}