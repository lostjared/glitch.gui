#include "acidcam/ac.h"

static constexpr int MAX = 8;
static ac::MatrixCollection<MAX> collection;

extern "C" void init() {
    std::cout << "picture_jump06 initalized...\n";
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
        srand(static_cast<unsigned int>(time(0)));
        collection.shiftFrames(frame);
    }
    else
        collection.shiftFrames(frame);
    static int dir = 1;
    static int offset = 0;
    static int size_x = frame.cols/16;
    
    for(int z = 0; z < frame.rows; ++z) {
        for(int i = 0; i < frame.cols; ++i) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            int cx = AC_GetFX(frame.cols-1, i, size_x);
            if(cx >= 0 && cx < frame.cols && z >= 0 && z < frame.rows) {
                cv::Vec3b &pix = collection.frames[offset].at<cv::Vec3b>(z, cx);
                pixel = pix;
            }
            
            if(dir == 1) {
                size_x ++;
                if(size_x > frame.cols*2)
                    dir = 0;
            } else {
                size_x --;
                if(size_x <= 0) {
                    dir = 1;
                    size_x = 0;
                }
            }
        }
    }
    
    if(++offset > (MAX-1)) {
        offset = 0;
    }
}
