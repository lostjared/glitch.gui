#include"colorxor2.hpp"

void ColorXor2::init() {
    srand(static_cast<unsigned int>(time(0)));
    alpha[0] = static_cast<double>(rand()%4);
    alpha[1] = static_cast<double>(rand()%4);
    alpha[2] = static_cast<double>(rand()%4);
    dir[0] = rand()%2;
    dir[1] = rand()%2;
    dir[2] = rand()%2;
}
 
void ColorXor2::proc(cv::Mat &frame) {
    for(int z = 0; z < frame.rows; z++) {
        for(int i = 0; i < frame.cols; i++) {
            cv::Vec3b &pixel = ac::pixelAt(frame, z, i);
            unsigned char value[3];
            for(int q = 0; q < 3; ++q) {
                value[q] = ac::wrap_cast(alpha[q] * pixel[q]);
                pixel[q] = pixel[q]^value[q];
            }
            
        }
    }
    for(int q = 0; q < 3; ++q) {
        double r = static_cast<double>(rand()%10);
        if(dir[q] == 1) {
            alpha[q] += 0.01*r;
            if(alpha[q] >= 3.0) {
                alpha[q] = 3.0;
                dir[q] = rand()%5;
            }
        } else if (dir[q] == 2) {
            alpha[q] -= 0.01*r;
            if(alpha[q] <= 1) {
                alpha[q] = 1.0;
                dir[q] = rand()%5;
            }
        } else if(dir[q] == 3) {
            alpha[q] += 0.01*r;
            if(alpha[q] >= 6.0) {
                alpha[q] = 6.0;
                dir[q] = rand()%5;
            }
        } else {
            alpha[q] -= 0.01*r;
            if(alpha[q] <= 1.5) {
                alpha[q] = 1.5;
                dir[q] = rand()%5;
            }
        }
    }
}
  
ColorXor2::~ColorXor2() {

}
