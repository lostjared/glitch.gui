#include "acidcam/ac.h"

static constexpr int MAX = 16;
static ac::MatrixCollection<MAX> collection;

extern "C" void init() {
    std::cout << "alphatrails initialized...\n";
    srand(static_cast<unsigned int>(time(0)));
}

extern "C" void rls() {
    ac::release_all_objects();
}

extern "C" void clear() {
    std::cout << "Clear called..\n";
    ac::release_all_objects();
}

extern "C" void proc(cv::Mat  &frame) {
    collection.shiftFrames(frame);
    cv::Mat *frames[3];
    frames[0] = &collection.frames[1];
    frames[1] = &collection.frames[7];
    frames[2] = &collection.frames[15];
    static double alpha = 0.1;
    auto callback = [&](cv::Mat *frame, int offset, int cols, int size) {
        for(int z = offset; z <  offset+size; ++z) {
            for(int i = 0; i < cols; ++i) {
                cv::Vec3b &pixel = frame->at<cv::Vec3b>(z, i);
                for(int j = 0; j < 3; ++j) {
                    cv::Vec3b pix = frames[j]->at<cv::Vec3b>(z, i);
                    pixel[j] = ac::wrap_cast((alpha * pixel[j]) + ((1-alpha) * pix[0]));
                }
            }
        }
    };
    ac::UseMultipleThreads(frame, ac::getThreadCount(), callback);
    static int dir = 1;
    if(dir == 1) {
        alpha += 0.05;
        if(alpha >= 1.0)
            dir = 0;
    } else {
        alpha -= 0.05;
        if(alpha <= 0.1)
            dir = 1;
    }
}
