#include "acidcam/ac.h"

extern "C" void init() {
    std::cout << "gpt initialized..\n";
    srand(static_cast<unsigned int>(time(0)));
}

extern "C" void rls() {
    ac::release_all_objects();
}

extern "C" void clear() {
    std::cout << "Clear called..\n";
    ac::release_all_objects();
}


extern "C" void proc(cv::Mat &frame) {
    if(frame.empty() || frame.channels() != 3) {
        std::cerr << "Invalid frame provided to proc function.\n";
        return;
    }

    const int blockSize = 10 + rand() % 20;
    const double colorShiftFactor = 0.5 + static_cast<double>(rand()) / RAND_MAX; 
    
    cv::Mat frame_clone = frame.clone();

    for(int y = 0; y < frame.rows; y += blockSize) {
        for(int x = 0; x < frame.cols; x += blockSize) {
            int actualBlockSizeY = std::min(blockSize, frame.rows - y);
            int actualBlockSizeX = std::min(blockSize, frame.cols - x);
            int sampleY = y + rand() % actualBlockSizeY;
            int sampleX = x + rand() % actualBlockSizeX;
            cv::Vec3b sampleColor = frame_clone.at<cv::Vec3b>(sampleY, sampleX);
            for(int by = 0; by < actualBlockSizeY; ++by) {
                for(int bx = 0; bx < actualBlockSizeX; ++bx) {
                    cv::Vec3b &pixel = frame.at<cv::Vec3b>(y + by, x + bx);
                    pixel[0] = std::min(255, std::max(0, int(sampleColor[0] * colorShiftFactor))); // B
                    pixel[1] = std::min(255, std::max(0, int(sampleColor[1] * colorShiftFactor))); // G
                    pixel[2] = std::min(255, std::max(0, int(sampleColor[2] * colorShiftFactor))); // R
                }
            }
        }
    }

    if(rand() % 2 == 0) {
        int startRow = rand() % frame.rows;
        int endRow = startRow + frame.rows / 2;
        endRow = std::min(endRow, frame.rows);

        for(int i = startRow; i < endRow; i++) {
            for(int j = 0; j < frame.cols; j++) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(i, j);
                pixel[0] = 255 - pixel[0]; // Invert Blue
                pixel[1] = 255 - pixel[1]; // Invert Green
                pixel[2] = 255 - pixel[2]; // Invert Red
            }
        }
    }
}