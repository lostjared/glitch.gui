#include "acidcam/ac.h"

static constexpr int MAX = 8;
static ac::MatrixCollection<MAX> collection;

extern "C" void init() {
    std::cout << "picture_jump01 initalized...\n";
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
    else if(rand()%5 == 0)
        collection.shiftFrames(frame);
    static int dir = 1;
    static int offset = 0;
    
    frame = collection.frames[offset].clone();
    
    if(dir == 1) {
        static int wait = 0;
        static int timeout = rand()%10;
        if(++offset > (MAX-1)) {
            offset = 0;
        }
        if(++wait > timeout) {
            wait = 0;
            timeout = rand()%10;
            dir = 0;
        }
    } else {
        static int wait = 0;
        static int timeout = rand()%10;
        if(--offset <= 0) {
            offset = MAX-1;
        }
        if(++wait > timeout) {
            wait = 0;
            timeout = rand()%10;
            dir = 1;
        }
    }
}
