#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include"acidcam/ac.h"

extern "C" void init() {
    std::cout << "VHS initialized..\n";
    srand(static_cast<unsigned int>(time(0)));
}

extern "C" void rls() {
    // Placeholder for actual implementation.
}

extern "C" void clear() {
    std::cout << "Clear called..\n";
    // Placeholder for actual implementation.
}

// Function to add horizontal line noise
void addHorizontalNoise(cv::Mat &frame, double alpha) {
    cv::Mat noise = cv::Mat(frame.size(), frame.type());
    cv::randu(noise, cv::Scalar::all(0), cv::Scalar::all(255)); // Create a noise image

    for (int y = 0; y < frame.rows; y += rand() % 5 + 1) { // Add noise lines with variable gaps
        for (int x = 0; x < frame.cols; ++x) {
            if (rand() % 10 < 3) { // 30% chance of being a noise line
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
                cv::Vec3b noisePixel = noise.at<cv::Vec3b>(y, x);
                for (int c = 0; c < 3; ++c) {
                    pixel[c] = static_cast<unsigned char>(alpha * pixel[c] + (1 - alpha) * noisePixel[c]);
                }
            }
        }
    }
}

// Function to simulate VHS color shift
void colorShift(cv::Mat &frame) {
    cv::Mat shifted_frame = frame.clone();

    for (int y = 0; y < frame.rows; ++y) {
        for (int x = 0; x < frame.cols; ++x) {
            int shift_val = (rand() % 5) - 2; // Random shift between -2 and 2
            if (x + shift_val >= 0 && x + shift_val < frame.cols) {
                cv::Vec3b color = frame.at<cv::Vec3b>(y, x);
                cv::Vec3b &shifted_color = shifted_frame.at<cv::Vec3b>(y, x + shift_val);
                shifted_color[1] = color[1]; // Shift green channel
            }
        }
    }
    frame = shifted_frame;
}


extern "C" void proc(cv::Mat &frame) {
    if (frame.empty() || frame.channels() != 3) {
        std::cerr << "Invalid frame provided to proc function.\n";
        return;
    }

    // Apply horizontal noise lines
    addHorizontalNoise(frame, 0.9); // Adjust alpha for noise transparency

    // Apply color channel shift
    colorShift(frame);

    // Optional: Apply additional effects like slight blurring to simulate VHS tape wear
    cv::GaussianBlur(frame, frame, cv::Size(3, 3), 0.5);
}
