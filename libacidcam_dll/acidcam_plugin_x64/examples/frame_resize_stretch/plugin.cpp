#include "acidcam/ac.h"

static constexpr int MAX = 16;
static ac::MatrixCollection<MAX> collection;

extern "C" void init() {
    std::cout << "frame_resize_stretch  initialized...\n";
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
    if(collection.empty()) {
        collection.shiftFrames(frame);
        srand(static_cast<unsigned int>(time(0)));
    } else
        collection.shiftFrames(frame);
    
    int frame_size = frame.cols/32;
    int frame_x_off = 0;
    static int off = 0;
    for(int z = 0; z < frame.rows; z++) {
        if(z%frame_size == 0) {
            ++off;
            if(off > MAX-1)
                off = 0;
            frame_x_off = rand()%(frame.cols/16);
        }
        for(int i = 0; i < frame.cols; ++i) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            cv::Mat &m = collection.frames[off];
            int off_x = AC_GetFX(frame.cols-1, i, frame.cols+frame_x_off);
            pixel = m.at<cv::Vec3b>(z, off_x);
        }
    }
}
