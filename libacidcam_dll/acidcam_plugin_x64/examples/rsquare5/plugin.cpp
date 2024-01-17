#include "acidcam/ac.h"

static constexpr int MAX = 8;
static ac::MatrixCollection<MAX> collection;

void drawSquare(cv::Mat &frame, int x, int y, int w, int h, cv::Mat &off) {
    for(int i = x; i < w; ++i) {
        for(int z = y; z < h; ++z) {
            if(i < frame.cols && z < frame.rows) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                pixel = off.at<cv::Vec3b>(z, i);
            }
        }
    }
}


extern "C" void init() {
    std::cout << "rsquare5 initialized...\n";
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
    
    static int offset = 0;
    
    for(int i = 0; i < (5+rand()%50); ++i) {
        int x = rand()%frame.cols;
        int y = rand()%frame.rows;
        int w = 10+rand()%(frame.cols-10);
        int h = 10+rand()%(frame.rows-10);
        drawSquare(frame, x, y, w, h, collection.frames[offset]);

        static int dir = 1;
        if(dir == 1) {
            if(++offset > MAX-1) {
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
    ac::FrameSep2(frame);
}
