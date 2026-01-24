#include "acidcam/ac.h"

static constexpr int MAX = 16;
static ac::MatrixCollection<MAX> collection;

extern "C" void init() {
    std::cout << "outoforder initialized..\n";
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
    else if(rand()%3 == 0)
        collection.shiftFrames(frame);
    
    static bool strobe = false;
    static int offset = 0;
    /*
    for(int z = 0; z < frame.rows; ++z) {
        for(int i = 0; i < frame.cols; ++i) {
            cv::Vec3b &pixel = ac::pixelAt(frame, z, i);
         
        }
    }*/
    
    if(strobe) {
        frame = collection.frames[offset].clone();
    }
    
    strobe = (strobe == true) ? false : true;
    static int cnt = 0;
    static int dir = 1;
    if(++cnt > 6) {
        if(dir == 1) {
        ++offset;
            if(offset > MAX-1) {
                dir = 0;
                offset = 2;
            }
            cnt = 0;
        } else {
            --offset;
            if(offset < 0) {
                offset = rand()%(MAX-1);
                dir = 1;
            }
        }
    }
}
