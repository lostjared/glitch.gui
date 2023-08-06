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

/* line down x4 */

void Glitch_Line_Down_X4::init() {
    offset_y = 0;
    color = cv::Vec3b(0, 0, 0);
    
}
void Glitch_Line_Down_X4::proc(cv::Mat &frame) {
    
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
            pixel[0] = pixel[0]|color[0];
            pixel[1] = pixel[1]|color[1];
            pixel[2] = pixel[2]|color[2];
        }
    }
    offset_y = rand()%frame.rows;
}

void Glitch_Line_Down_X4::clear() {}
Glitch_Line_Down_X4::~Glitch_Line_Down_X4() {}

/* line down x5 */

void Glitch_Line_Down_X5::init() {
    offset_y = 0;
    color = cv::Vec3b(0, 0, 0);
}

void Glitch_Line_Down_X5::proc(cv::Mat &frame) {
    int width=5+rand()%50;
    for(int x2 = 0; x2 < frame.cols; x2 += width) {
        for(int x = x2; x < x2+width && x < frame.cols; ++x) {
            color = cv::Vec3b(rand()%255, rand()%255, rand()%255);
            for(int y = 0; y < offset_y && y < frame.rows; ++y) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
                pixel[0] += pixel[0]^color[0];
                pixel[1] += pixel[1]^color[1];
                pixel[2] += pixel[2]^color[2];
            }
            for(int y = offset_y; y < frame.rows; ++y) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
                pixel[0] = pixel[0]|color[0];
                pixel[1] = pixel[1]|color[1];
                pixel[2] = pixel[2]|color[2];
            }
        }
        width=5+rand()%50;
        
    }
    offset_y = rand()%frame.rows;
}

void Glitch_Line_Down_X5::clear() {}
Glitch_Line_Down_X5::~Glitch_Line_Down_X5() {}

/* rand rect */

void Glitch_RandRect::init() {

}
 
void Glitch_RandRect::proc(cv::Mat &frame) {
    int rand_rects = 25+rand()%50;
    for(int i = 0; i < rand_rects; ++i) {
        int x = rand()%frame.cols;
        int y = rand()%frame.rows;
        int w = rand()%frame.cols;
        int h = rand()%frame.rows;
        cv::Vec3b color = cv::Vec3b(rand()%255, rand()%255, rand()%255);
        blendRect(frame, color, x, y, w, h);
    }
}
 
void Glitch_RandRect::clear() {}
Glitch_RandRect::~Glitch_RandRect() {}

void Glitch_RandRect::blendRect(cv::Mat &frame, cv::Vec3b &color, int x, int y, int w, int h) {
    for(int i = x; i < w && i < frame.cols; ++i) {
        for(int z = y; z < h && z < frame.rows; ++z) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            for(int q = 0; q < 3; ++q) {
                pixel[q] = ac::wrap_cast((0.7 * color[q]) + (0.3 * pixel[q]));
            }    
        }
    }
}

/* rand rect x2*/

void Glitch_RandRect_X2::init() {

}
 
void Glitch_RandRect_X2::proc(cv::Mat &frame) {
    int rand_rects = 25+rand()%50;
    for(int i = 0; i < rand_rects; ++i) {
        int x = rand()%frame.cols;
        int y = rand()%frame.rows;
        int w = rand()%frame.cols;
        int h = rand()%frame.rows;
        cv::Vec3b color = cv::Vec3b(rand()%255, rand()%255, rand()%255);
        if(x >= 0 && x < frame.cols && y >= 0 && y < frame.rows)
            color = frame.at<cv::Vec3b>(y, x);
            
        blendRect(frame, color, x, y, w, h);
    }
}
 
void Glitch_RandRect_X2::clear() {}
Glitch_RandRect_X2::~Glitch_RandRect_X2() {}

void Glitch_RandRect_X2::blendRect(cv::Mat &frame, cv::Vec3b &color, int x, int y, int w, int h) {
    for(int i = x; i < w && i < frame.cols; ++i) {
        for(int z = y; z < h && z < frame.rows; ++z) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            for(int q = 0; q < 3; ++q) {
                pixel[q] = ac::wrap_cast((0.7 * color[q]) + (0.3 * pixel[q]));
            }    
        }
    }
}


/* rand rect x2 wrap*/

void Glitch_RandRect_X2_Wrap::init() {

}
 
void Glitch_RandRect_X2_Wrap::proc(cv::Mat &frame) {
    int rand_rects = 25+rand()%50;
    for(int i = 0; i < rand_rects; ++i) {
        int x = rand()%frame.cols;
        int y = rand()%frame.rows;
        int w = rand()%frame.cols;
        int h = rand()%frame.rows;
        cv::Vec3b color = cv::Vec3b(rand()%255, rand()%255, rand()%255);
        if(x >= 0 && x < frame.cols && y >= 0 && y < frame.rows)
            color = frame.at<cv::Vec3b>(y, x);
            
        blendRect(frame, color, x, y, w, h);
    }
}
 
void Glitch_RandRect_X2_Wrap::clear() {}
Glitch_RandRect_X2_Wrap::~Glitch_RandRect_X2_Wrap() {}

void Glitch_RandRect_X2_Wrap::blendRect(cv::Mat &frame, cv::Vec3b &color, int x, int y, int w, int h) {
    for(int i = x; i < w && i < frame.cols; ++i) {
        for(int z = y; z < h && z < frame.rows; ++z) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            for(int q = 0; q < 3; ++q) {
                pixel[q] = ac::wrap_cast((0.7 * color[q]) + (0.7 * pixel[q]));
            }    
        }
    }
}

/* rect x3 */

void Glitch_RandRect_X3::init() {

}
 
void Glitch_RandRect_X3::proc(cv::Mat &frame) {
    int rand_rects = 25+rand()%50;
    for(int i = 0; i < rand_rects; ++i) {
        int x = rand()%frame.cols;
        int y = rand()%frame.rows;
        int w = rand()%frame.cols;
        int h = rand()%frame.rows;
        cv::Vec3b color = cv::Vec3b(rand()%255, rand()%255, rand()%255);
        if(x >= 0 && x < frame.cols && y >= 0 && y < frame.rows)
            color = frame.at<cv::Vec3b>(y, x);
            
        blendRect(frame, color, x, y, w, h);
    }
}
 
void Glitch_RandRect_X3::clear() {}
Glitch_RandRect_X3::~Glitch_RandRect_X3() {}

void Glitch_RandRect_X3::blendRect(cv::Mat &frame, cv::Vec3b &color, int x, int y, int w, int h) {
    for(int i = x; i < w && i < frame.cols; ++i) {
        for(int z = y; z < h && z < frame.rows; ++z) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            for(int q = 0; q < 3; ++q) {
                pixel[q] = ac::wrap_cast((0.7 * color[q]) + (0.3 * pixel[q]));
            }    
        }
    }
}