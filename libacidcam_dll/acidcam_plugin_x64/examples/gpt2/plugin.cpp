// written by ChatGPT-4
#include "acidcam/ac.h"

extern "C" void init() {
    std::cout << "gpt2 initialized..\n";
    srand(static_cast<unsigned int>(time(0)));
}

extern "C" void rls() {
    ac::release_all_objects();
}

extern "C" void clear() {
    ac::release_all_objects();
}

extern "C" void proc(cv::Mat &frame) {
    cv::Mat temp_frame = frame.clone();
    for(int y = 0; y < frame.rows; y++) {
        for(int x = 0; x < frame.cols; x++) {
            int dx = static_cast<int>(25.0 * sin(2 * 3.14 * y / 180.0));
            int dy = static_cast<int>(25.0 * cos(2 * 3.14 * x / 180.0));
            int new_x = x + dx;
            int new_y = y + dy;
            if(new_x >= 0 && new_x < frame.cols && new_y >= 0 && new_y < frame.rows) {
                frame.at<cv::Vec3b>(y, x) = temp_frame.at<cv::Vec3b>(new_y, new_x);
            }
        }
    }
}