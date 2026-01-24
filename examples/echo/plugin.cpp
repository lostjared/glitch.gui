#include "acidcam/ac.h"


extern "C" void init() {
    std::cout << "echo initialized...\n";
    srand(static_cast<unsigned int>(time(0)));
}

extern "C" void rls() {
    ac::release_all_objects();
}

extern "C" void clear() {
    std::cout << "Clear called..\n";
    ac::release_all_objects();
}



extern "C" void proc(cv::Mat  &inputImage) {
    cv::Mat resized1, resized2, resized3;
    cv::Mat color, color2, color3, color4;
    color = inputImage.clone();
    cv::resize(inputImage, resized1, cv::Size(), 0.5, 0.5, cv::INTER_LINEAR);
    cv::resize(inputImage, resized2, cv::Size(), 0.25, 0.25, cv::INTER_LINEAR);
    cv::resize(inputImage, resized3, cv::Size(), 0.125, 0.125, cv::INTER_LINEAR);
    cv::resize(resized1, color2, inputImage.size(), 0, 0, cv::INTER_LINEAR);
    cv::resize(resized2, color3, inputImage.size(), 0, 0, cv::INTER_LINEAR);
    cv::resize(resized3, color4, inputImage.size(), 0, 0, cv::INTER_LINEAR);
    cv::Mat outputImage = (color * 0.4 + color2 * 0.4 + color3 * 0.4 + color4 * 0.4);
    inputImage = outputImage;
}


