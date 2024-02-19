#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include"acidcam/ac.h"

extern "C" void init() {
    std::cout << "invertflash initialized..\n";
    srand(static_cast<unsigned int>(time(0)));
}

extern "C" void rls() {
    // Placeholder for actual implementation.
    ac::release_all_objects();
}

extern "C" void clear() {
    std::cout << "Clear called..\n";
    ac::release_all_objects();
}

static ac::MatrixCollection<8> collection;

extern "C" void proc(cv::Mat &frame) {
    if(collection.empty())
        collection.shiftFrames(frame);
    else
        collection.shiftFrames(frame);
    
    for(int z = 0; z < frame.rows; ++z) {
        for(int i = 0; i < frame.cols; ++i) {
            cv::Vec3b &pixel = ac::pixelAt(frame, z, i);
            cv::Vec3b pix[4];
            pix[0] = ac::pixelAt(collection.frames[1], z, i);
            pix[1] = ac::pixelAt(collection.frames[4], z, i);
            pix[2] = ac::pixelAt(collection.frames[7], z, i);
            
            // Check if the current pixel is significantly different from the corresponding pixel in the MatrixCollection
            if(cv::norm(pixel - pix[0]) > 10 || cv::norm(pixel - pix[1]) > 10 || cv::norm(pixel - pix[2]) > 10) {
                // Generate a random color for the pixel


                cv::Vec3b random_color = cv::Vec3b(rand() % 256, rand() % 256, rand() % 256);
                pixel = random_color;
            }
        }
    }
    
    // Optional: Add an invert effect at the end if desired
    // AddInvert(frame);
}
