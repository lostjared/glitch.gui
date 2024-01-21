#include "acidcam/ac.h"

static constexpr int MAX = 8;
static ac::MatrixCollection<MAX> collection;

extern "C" void init() {
    std::cout << "glitch_x1 initialized...\n";
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
    
    auto drawRect = [&](cv::Mat &col_frame, int x, int y, int w, int h) {
        for(int z = y; z < y+h && z < frame.rows; ++z) {
            for(int i = x; i < x+w && i < frame.cols; ++i) {
                if(i >= 0 && i < frame.cols && z >= 0 && z < frame.rows) {
                    frame.at<cv::Vec3b>(z, i) = col_frame.at<cv::Vec3b>(z, i);
                }
            }
        }
    };
    
    int size = frame.rows/4;
    static int offset = 0;
    
    for(int j = 0; j < 4; ++j) {
  
        if(!(rand()%4 == 0)) continue;
        
        drawRect(collection.frames[offset], 0, size*j, frame.cols, size);
    
        if(++offset > (MAX-1))
            offset = 0;
    }
}
