#include "acidcam/ac.h"

static constexpr int MAX = 8;
static ac::MatrixCollection<MAX> collection;

extern "C" void init() {
    std::cout << "distort_picture initialized...\n";
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
    
    int width = 1+(rand()%frame.cols);
    int skip = 0;
    static int offset = 0;
    
    for(int z = 0; z < frame.rows; ++z) {
        for(int i = 0; i < frame.cols; ++i) {
            cv::Vec3b &pixel = ac::pixelAt(frame, z, i);
            
            int offx = AC_GetFX(frame.cols-1, i, width);
            
            cv::Vec3b &cpix = collection.frames[offset].at<cv::Vec3b>(z, offx);
        
            pixel = cpix;
        }
        width += 1+(rand()%5);
        if(width%10) {
            if(++offset > (MAX-1))
                offset = 0;
        }
        
    }
}
