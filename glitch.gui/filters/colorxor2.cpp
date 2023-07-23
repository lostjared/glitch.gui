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

void ColorXor3::init() {
   srand(static_cast<unsigned int>(time(0)));
   alpha[0] = static_cast<double>(rand()%4);
   alpha[1] = static_cast<double>(rand()%4);
   alpha[2] = static_cast<double>(rand()%4); 
   dir[0] = rand()%2;
   dir[1] = rand()%2;
   dir[2] = rand()%2;

}

void ColorXor3::proc(cv::Mat &frame) {
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
            alpha[q] += 0.005*r;
            if(alpha[q] >= max_x[q]) {
                alpha[q] = max_x[q];
                dir[q] = rand()%2;
                double r2 = static_cast<double>(rand()%10);
                double rv = 0.01*r2;
                max_x[q] += rv;
                if(max_x[q] >= 3.0)
                    max_x[q] = 3.0;
            }
        } else {
            alpha[q] -= 0.005*r;
            if(alpha[q] <= min_x[q]) {
                alpha[q] = min_x[q];
                dir[q] = rand()%2;
                double r2 = static_cast<double>(rand()%10);
                double rv = 0.01*r2;
                min_x[q] -= rv;
                if(min_x[q] <= 1)
                    min_x[q] = 1;
            }
        }
    }
}


ColorXor3::~ColorXor3() {

}

void ColorXor4::init() {
    srand(static_cast<unsigned int>(time(0)));
    alpha[0] = static_cast<double>(rand()%4);
    alpha[1] = static_cast<double>(rand()%4);
    alpha[2] = static_cast<double>(rand()%4);
    dir[0] = rand()%2;
    dir[1] = rand()%2;
    dir[2] = rand()%2;
    max_x = 1.0;
    min_x = 1.0;
}


void ColorXor4::proc(cv::Mat &frame) {
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
            if(alpha[q] >= max_x) {
                alpha[q] = max_x;
                dir[q] = rand()%2;
                double r2 = static_cast<double>(rand()%10);
                double rv = 0.01*r2;
                max_x += rv;
                if(max_x >= 3.0)
                    max_x = 3.0;
            }
        } else {
            alpha[q] -= 0.01*r;
            if(alpha[q] <= min_x) {
                alpha[q] = min_x;
                dir[q] = rand()%2;
                double r2 = static_cast<double>(rand()%10);
                double rv = 0.01*r2;
                min_x -= rv;
                if(min_x <= 1)
                    min_x = 1;
            }
        }
    }
}

ColorXor4::~ColorXor4() {

}

void ColorXor5::init() {
    alpha[0] = 1.0;
    alpha[1] = 3.0;
    alpha[2] = 1.0;
    dir[0] = 1;
    dir[1] = 0;
    dir[2] = 1;
}
 
void ColorXor5::proc(cv::Mat &frame) {
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
        if(dir[q] == 1) {
            alpha[q] += 0.01;
            if(alpha[q] >= 3.0) {
                alpha[q] = 3.0;
                dir[q] = 0;
            }
        } else {
            alpha[q] -= 0.01;
            if(alpha[q] <= 1) {
                alpha[q] = 1.0;
                dir[q] = 1;
            }
        }
    }
}
 
ColorXor5::~ColorXor5() {

}
