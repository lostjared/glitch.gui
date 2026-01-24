#include "acidcam/ac.h"


static constexpr int MAX = 4;
static ac::MatrixCollection<MAX> collection;
    

extern "C" void init() {
    std::cout << "store_frame10 initialized..\n";
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
    if(collection.empty()) {
        srand(static_cast<unsigned int>(time(0)));
        collection.shiftFrames(frame);
    }
    static int counter = 0;
    if(++counter > 4) {
        counter = 0;
        collection.shiftFrames(frame);
    }
    static int offset = 0;
    for(int z = 0; z < frame.rows; ++z) {
        for(int i = 0; i < frame.cols; ++i) {
            cv::Vec3b &pixel = ac::pixelAt(frame, z, i);
            cv::Vec3b &pix = ac::pixelAt(collection.frames[offset], z, i);
            pixel = pix;
        }
    }
    if(++offset > (MAX-1)) {
        offset = 0;
    }
}