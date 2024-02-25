// written by ChatGPT-4
#include "acidcam/ac.h"

extern "C" void init() {
    std::cout << "gpt2 initialized..\n";
    srand(static_cast<unsigned int>(time(0)));
}

extern "C" void rls() {
    ac::release_all_objects();
}

extern "C" void clear() {
    ac::release_all_objects();
}
static int time_counter = 0;

extern "C" void proc(cv::Mat &frame) {
    cv::Mat temp_frame = frame.clone();
    // Parameters to customize the wave effect
    double amplitude = 25.0; // Amplitude of the wave
    double frequency = 2 * 3.14 / 180.0; // Frequency of the wave
    double phase_shift_speed = 0.05; // Speed of the phase shift change

    // Update phase shift based on time_counter
    double phase_shift_x = time_counter * phase_shift_speed;
    double phase_shift_y = time_counter * phase_shift_speed;

    for(int y = 0; y < frame.rows; y++) {
        for(int x = 0; x < frame.cols; x++) {
            // Applying moving wave distortion with dynamic phase shifts
            int dx = static_cast<int>(amplitude * sin(frequency * y + phase_shift_y));
            int dy = static_cast<int>(amplitude * cos(frequency * x + phase_shift_x));
            int new_x = x + dx;
            int new_y = y + dy;

            // Ensuring new positions are within image bounds before accessing
            if(new_x >= 0 && new_x < frame.cols && new_y >= 0 && new_y < frame.rows) {
                frame.at<cv::Vec3b>(y, x) = temp_frame.at<cv::Vec3b>(new_y, new_x);
            }
        }
    }
    // Increment the time counter for the next frame/call
    time_counter++;
}