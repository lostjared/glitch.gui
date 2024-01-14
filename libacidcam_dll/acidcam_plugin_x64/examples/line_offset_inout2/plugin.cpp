#include "acidcam/ac.h"


static constexpr int MAX = 4;
static ac::MatrixCollection<MAX> collection;
    

extern "C" void init() {
    std::cout << "line_offset_inout2 initialized..\n";
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
    else
        collection.shiftFrames(frame);
    
    static int offset = 0;
    static int num = 1+(rand()%100);
    
    for(int z = 0; z < frame.rows; ++z) {
        for(int i = 0; i < frame.cols; ++i) {
            cv::Vec3b &pixel = ac::pixelAt(frame, z, i);
            cv::Vec3b &pix = collection.frames[offset].at<cv::Vec3b>(z, i);
            pixel = pix;
        }
        if((z%num) == 0) {
            num = 1+(rand()%250);
            static int dir = 1;
            if(dir == 1) {
                if(++offset > (MAX-1)) {
                    offset = MAX-1;
                    dir = 0;
                }
            } else {
                if(--offset <= 0) {
                    offset = 0;
                    dir = 1;
                }
            }
        }
    }
}
