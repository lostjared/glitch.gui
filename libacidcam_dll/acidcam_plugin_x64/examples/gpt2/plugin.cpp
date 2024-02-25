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
    /*
    int num_regions = 10;
    for(int i = 0; i < num_regions; i++) {
        int x_start = rand() % frame.cols;
        int y_start = rand() % frame.rows;
        int region_width = std::min(50 + (rand() % 50), frame.cols - x_start);
        int region_height = std::min(50 + (rand() % 50), frame.rows - y_start);
        for(int y = y_start; y < (y_start + region_height); y++) {
            for(int x = x_start; x < (x_start + region_width); x++) {
                int dx = x_start + rand() % region_width;
                int dy = y_start + rand() % region_height;
                if(dx < frame.cols && dy < frame.rows) {
                    cv::Vec3b color = frame.at<cv::Vec3b>(y, x);
                    frame.at<cv::Vec3b>(dy, dx) = color;
                }
            }
        }
    }*/

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