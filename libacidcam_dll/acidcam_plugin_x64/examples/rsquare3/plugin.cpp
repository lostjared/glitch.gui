#include "acidcam/ac.h"

static constexpr int MAX = 8;
static ac::MatrixCollection<MAX> collection;

void drawSquare(cv::Mat &frame, int x, int y, int w, int h, cv::Mat &off) {
    for(int i = x; i < w; ++i) {
        for(int z = y; z < h; ++z) {
            if(i < frame.cols && z < frame.rows) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                cv::Vec3b pix;
                pix = off.at<cv::Vec3b>(z, i);
                for(int j = 0; j < 3; ++j)
                pixel[j] = ac::wrap_cast((0.5 * pixel[j]) + (0.5 * pix[j]));
            }
        }
    }
}

extern "C" void init() {
    std::cout << "rsquare3 initialized...\n";
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
    collection.shiftFrames(frame);
    for(int i = 0; i < (50+rand()%50); ++i) {
        int x = rand()%frame.cols;
        int y = rand()%frame.rows;
        int w = 10+rand()%(frame.cols-10);
        int h = 10+rand()%(frame.rows-10);
        drawSquare(frame, x, y, w, h, collection.frames[rand()%(MAX-1)]);
    }
    ac::FrameSep2(frame);
}
