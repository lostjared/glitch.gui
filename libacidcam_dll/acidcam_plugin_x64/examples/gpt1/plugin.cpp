#include "acidcam/ac.h"


extern "C" void init() {
    std::cout << "gpt initialized..\n";
    srand(static_cast<unsigned int>(time(0)));
}

extern "C" void rls() {
    ac::release_all_objects();
}

extern "C" void clear() {
    std::cout << "Clear called..\n";
    ac::release_all_objects();
}

extern "C" void proc(cv::Mat &frame) {
    if(frame.empty() || frame.channels() != 3) {
        std::cerr << "Invalid frame provided to proc function.\n";
        return;
    }

    int row_shift = rand() % (frame.rows / 4);
    int col_shift = rand() % (frame.cols / 4);

    cv::Mat frame_clone = frame.clone();

    for(int i = 0; i < frame.rows; i++) {
        for(int j = 0; j < frame.cols; j++) {
            if(j + col_shift < frame.cols) {
                frame.at<cv::Vec3b>(i, j)[2] = frame_clone.at<cv::Vec3b>(i, (j + col_shift) % frame.cols)[2];
            }

            if(i + row_shift < frame.rows) {
                frame.at<cv::Vec3b>(i, j)[1] = frame_clone.at<cv::Vec3b>((i + row_shift) % frame.rows, j)[1];
            }

            if(rand() % 5 == 0) { // 20% chance of altering the blue channel
                frame.at<cv::Vec3b>(i, j)[0] = rand() % 256;
            }
        }
    }

    if(rand() % 2 == 0) { 
        cv::bitwise_not(frame, frame);
    }
}