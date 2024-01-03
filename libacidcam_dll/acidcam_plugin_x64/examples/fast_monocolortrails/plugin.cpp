#include"frame_collection.hpp"


static ac::MatrixCollection<16> collection;
 
extern "C" void init() {
    std::cout << "plugin initialized..\n";
}

extern "C" void rls() {
    ac::release_all_objects();
}

extern "C" void clear() {
    std::cout << "Clear called..\n";
    ac::release_all_objects();
}

extern "C" void proc(cv::Mat &frame) {
    collection.shiftFrames(frame);
    cv::Mat *frames[3];
    frames[0] = &collection.frames[1];
    frames[1] = &collection.frames[7];
    frames[2] = &collection.frames[15];
    auto callback = [&](cv::Mat *frame, int offset, int cols, int size) {
        for(int z = offset; z <  offset+size; ++z) {
            for(int i = 0; i < cols; ++i) {
                cv::Vec3b &pixel = frame->at<cv::Vec3b>(z, i);
                for(int j = 0; j < 3; ++j) {
                    cv::Vec3b pix = frames[j]->at<cv::Vec3b>(z, i);
                    pixel[j] = pix[0];
                }
            }
        }
    };
    ac::UseMultipleThreads(frame, ac::getThreadCount(), callback);
}