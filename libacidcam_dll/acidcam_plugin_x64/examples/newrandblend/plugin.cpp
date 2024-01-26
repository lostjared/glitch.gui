#include "acidcam/ac.h"

static constexpr int MAX = 16;
static ac::MatrixCollection<MAX> collection;

extern "C" void init() {
    std::cout << "newrandblend initialized...\n";
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
    ac::DetectEdges(frame);
    collection.shiftFrames(frame);
    int off = MAX-1;
    int m = 0;
    for(int z = 0; z < frame.rows; ++z) {
        ++m;
        if(m > MAX-1) {
            m = 0;
            off--;
            if(off < 1)
                off = MAX-1;
        }
        for(int i = 0; i < frame.cols; ++i) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            cv::Mat &m = collection.frames[off];
            cv::Vec3b &pix = m.at<cv::Vec3b>(z, i);
            pixel = pix;
        }
    }
}
