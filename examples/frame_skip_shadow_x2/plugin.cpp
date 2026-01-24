#include "acidcam/ac.h"

static constexpr int MAX = 16;
static ac::MatrixCollection<MAX> collection;

extern "C" void init() {
    std::cout << "frame_skip_shadow_x2 initialized...\n";
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
        collection.shiftFrames(frame);
        srand(static_cast<unsigned int>(time(0)));
    } else if(rand()%5==0)
        collection.shiftFrames(frame);
    static bool on = false;
    static int off = 0;
    if(on == true) {
        cv::Mat &f2 = collection.frames[MAX-2];
        
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                cv::Mat &f = collection.frames[off];
                cv::Vec3b pix = f.at<cv::Vec3b>(z, i);
                cv::Vec3b pix2 = f2.at<cv::Vec3b>(z, i);
                for(int q = 0; q < 3; ++q)
                    pixel[q] = ac::wrap_cast((pixel[q] * 0.33) + (pix[q] * 0.33) + (pix2[q] * 0.33));
            }
        }
    }

    static int dir = 1;
    
    if(dir == 1) {
        off++;
        if(off > MAX-1) {
            off = MAX-1;
            dir = 0;
        }
    } else {
        off--;
        if(off <= 0) {
            off = 0;
            dir = 1;
        }
    }
    static int cnt = 0;
    static int wait = rand()%20;
    ++cnt;
    if(cnt > wait) {
        on = !on;
        cnt = 0;
        wait = rand()%20;
    }
}
