#include"glitch.hpp"

void Glitch_Line_Down::init() {
    offset_y = rand()%300;
    color = cv::Vec3b(150, 150, 150);    
}

void Glitch_Line_Down::proc(cv::Mat &frame) {
    for(int x = 0; x < frame.cols; ++x) {
        color = cv::Vec3b(rand()%255, rand()%255, rand()%255);
        for(int y = 0; y < offset_y && y < frame.rows; ++y) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
            pixel[0] += pixel[0]*color[0];
            pixel[1] += pixel[1]*color[1];
            pixel[2] += pixel[2]*color[2];
        }
        offset_y = rand()%frame.rows;
    }
}

void Glitch_Line_Down::clear() {}

Glitch_Line_Down::~Glitch_Line_Down() {}

/* line down x2 */

void Glitch_Line_Down_X2::init() {
    offset_y = 0;
    color = cv::Vec3b(0, 0, 0);
}


void Glitch_Line_Down_X2::proc(cv::Mat &frame) {
    for(int x = 0; x < frame.cols; ++x) {
        color = cv::Vec3b(rand()%255, rand()%255, rand()%255);
        for(int y = 0; y < offset_y && y < frame.rows; ++y) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
            pixel[0] += pixel[0]*color[0];
            pixel[1] += pixel[1]*color[1];
            pixel[2] += pixel[2]*color[2];
        }
        for(int y = offset_y; y < frame.rows; ++y) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
            pixel[0] = pixel[0]*color[0];
            pixel[1] = pixel[1]*color[1];
            pixel[2] = pixel[2]*color[2];
        }
        offset_y = rand()%frame.rows;
    }
}
 
void Glitch_Line_Down_X2::clear() {}

Glitch_Line_Down_X2::~Glitch_Line_Down_X2() {}

/* line down 3 */

void Glitch_Line_Down_X3::init() {
    offset_y = 0;
    color = cv::Vec3b(0, 0, 0);
}

void Glitch_Line_Down_X3::proc(cv::Mat &frame) {
    for(int x = 0; x < frame.cols; ++x) {
        color = cv::Vec3b(rand()%255, rand()%255, rand()%255);
        for(int y = 0; y < offset_y && y < frame.rows; ++y) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
            pixel[0] += pixel[0]^color[0];
            pixel[1] += pixel[1]^color[1];
            pixel[2] += pixel[2]^color[2];
        }
        for(int y = offset_y; y < frame.rows; ++y) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
            pixel[0] = pixel[0]&color[0];
            pixel[1] = pixel[1]&color[1];
            pixel[2] = pixel[2]&color[2];
        }
        offset_y = rand()%frame.rows;
    }
}
void Glitch_Line_Down_X3::clear() {}
Glitch_Line_Down_X3::~Glitch_Line_Down_X3() {}