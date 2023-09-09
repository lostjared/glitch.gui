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
                pixel[q] += ac::wrap_cast((0.7 * color[q]) + (0.3 * pixel[q]));
            }    
        }
    }
}

/* rect x4 */

void Glitch_RandRect_X4::init() {

}
 
void Glitch_RandRect_X4::proc(cv::Mat &frame) {
    int rand_rects = 25+rand()%50;
    for(int i = 0; i < rand_rects; ++i) {
        int x = rand()%frame.cols;
        int y = rand()%frame.rows;
        int w = rand()%frame.cols;
        int h = rand()%frame.rows;
        cv::Vec3b color = cv::Vec3b(rand()%255, rand()%255, rand()%255);
        cv::Vec3b color2 = cv::Vec3b(0, 0, 0);
        if(x >= 0 && x < frame.cols && y >= 0 && y < frame.rows)
            color2 = frame.at<cv::Vec3b>(y, x);
            
        blendRect(frame, color, color2, x, y, w, h);
    }
}
 
void Glitch_RandRect_X4::clear() {}
Glitch_RandRect_X4::~Glitch_RandRect_X4() {}

void Glitch_RandRect_X4::blendRect(cv::Mat &frame, cv::Vec3b &color, cv::Vec3b &color2, int x, int y, int w, int h) {
    for(int i = x; i < w && i < frame.cols; ++i) {
        for(int z = y; z < h && z < frame.rows; ++z) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            for(int q = 0; q < 3; ++q) {
               pixel[q] |= ac::wrap_cast((0.3 * color[q]) + (0.3 * pixel[q]) + (0.3 * color2[q]));
            }    
        }
    }
}

/* pixel x1 */

void Glitch_Pixel_X1::init() {

}

void Glitch_Pixel_X1::proc(cv::Mat &frame) {
    int rand_rects = 25+rand()%25;
    for(int i = 0; i < rand_rects; ++i) {
        int x = rand()%frame.cols;
        int y = rand()%frame.rows;
        int w = rand()%frame.cols;
        int h = rand()%frame.rows; 
        fillRect(frame, x, y, w, h);
    }
}

void Glitch_Pixel_X1::clear() {

}

Glitch_Pixel_X1::~Glitch_Pixel_X1() {

}


void Glitch_Pixel_X1::fillRect(cv::Mat &frame, int x, int y, int w, int h) {
    
       for(int i = x; i < w && i < frame.cols; ++i) {
        for(int z = y; z < h && z < frame.rows; ++z) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            for(int q = 0; q < 3; ++q) {
                cv::Vec3b color(rand()%255, rand()%255, rand()%255);
                pixel[q] += ac::wrap_cast((0.2 * color[q]) + (0.8 * pixel[q]));
            }    
        }
    }
 
}

/* Glitch Mirror Shift */


void Glitch_Mirror_Shift::init() {
    size_x = 0;
}

void Glitch_Mirror_Shift::proc(cv::Mat &frame) {
    collection.shiftFrames(frame);
    int width = frame.cols/collection.count();
    int x_pos = 0;

    for(size_t i = 0; i < collection.count(); ++i) {
        drawMatrix(frame, collection[rand()%collection.count()], size_x, x_pos, width);
        size_x += 25;
        x_pos += width;
    }
    if(size_x > frame.cols)
        size_x = 0;
}

void Glitch_Mirror_Shift::clear() {
    collection.clear();
}

Glitch_Mirror_Shift::~Glitch_Mirror_Shift() {

}

void Glitch_Mirror_Shift::drawMatrix(cv::Mat &frame, const cv::Mat &src, int off, int x, int w) {
    for(int i = x; i < x+w && i < frame.cols; ++i) {
        for(int z = 0; z < frame.rows; ++z) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            if(i+off < frame.cols) {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, i+off);
                for(int q = 0; q < 3; ++q) {
                    pixel[q] = ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));
                }
            }
        }
    }
}

/* Glitch Mirror Shift Xor */


void Glitch_Mirror_Shift_Xor::init() {
    size_x = 0;
}

void Glitch_Mirror_Shift_Xor::proc(cv::Mat &frame) {
    collection.shiftFrames(frame);
    int width = frame.cols/collection.count();
    int x_pos = 0;

    for(size_t i = 0; i < collection.count(); ++i) {
        drawMatrix(frame, collection[rand()%collection.count()], size_x, x_pos, width);
        size_x += 25;
        x_pos += width;
    }
    if(size_x > frame.cols)
        size_x = 0;
}

void Glitch_Mirror_Shift_Xor::clear() {
    collection.clear();
}

Glitch_Mirror_Shift_Xor::~Glitch_Mirror_Shift_Xor() {

}

void Glitch_Mirror_Shift_Xor::drawMatrix(cv::Mat &frame, const cv::Mat &src, int off, int x, int w) {
    for(int i = x; i < x+w && i < frame.cols; ++i) {
        for(int z = 0; z < frame.rows; ++z) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            if(i+off < frame.cols) {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, i+off);
                for(int q = 0; q < 3; ++q) {
                    pixel[q] ^= ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));
                }
            }
        }
    }
}

/* Glitch Mirror Slice */


void Glitch_Mirror_Slice::init() {
    size_x = 0;
}

void Glitch_Mirror_Slice::proc(cv::Mat &frame) {
    collection.shiftFrames(frame);
    int width = frame.cols/collection.count();
    int offset = 0;
    for(size_t i = 0; i < collection.count(); ++i) {
        drawMatrix(frame, collection[i%collection.count()], rand()%frame.cols, offset, width);
        offset += width;
    }
}

void Glitch_Mirror_Slice::clear() {
    collection.clear();
}

Glitch_Mirror_Slice::~Glitch_Mirror_Slice() {

}

void Glitch_Mirror_Slice::drawMatrix(cv::Mat &frame, const cv::Mat &src, int off, int x, int w) {
    for(int i = x; i < x+w && i < frame.cols; ++i) {
        for(int z = 0; z < frame.rows; ++z) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            if(i + off < frame.cols) {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, off+i);
                for(int q = 0; q < 3; ++q)
                    pixel[q] = ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));
            }
        }
    }
}

/* Glitch Mirror Slice Rand*/


void Glitch_Mirror_Slice_Rand::init() {
    size_x = 0;
}

void Glitch_Mirror_Slice_Rand::proc(cv::Mat &frame) {
    collection.shiftFrames(frame);
    int width = frame.cols/collection.count();
    int offset = 0;
    for(size_t i = 0; i < collection.count() * 2; ++i) {
        drawMatrix(frame, collection[i%collection.count()], rand()%frame.cols, offset, width);
        offset += width;
    }
}

void Glitch_Mirror_Slice_Rand::clear() {
    collection.clear();
}

Glitch_Mirror_Slice_Rand::~Glitch_Mirror_Slice_Rand() {

}

void Glitch_Mirror_Slice_Rand::drawMatrix(cv::Mat &frame, const cv::Mat &src, int off, int x, int w) {
    for(int i = x; i < x+w && i < frame.cols; ++i) {
        int row_size = rand()%frame.rows;
        for(int z = 0; z < row_size; ++z) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            if(i + off < frame.cols) {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, off+i);
                for(int q = 0; q < 3; ++q)
                    pixel[q] = ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));
            }
        }
    }
}

/* Glitch Mirror Slice Inc */

void Glitch_Mirror_Slice_Inc::init() {
    size_x = 0;
    rsize_val = 0;
}

void Glitch_Mirror_Slice_Inc::proc(cv::Mat &frame) {
    collection.shiftFrames(frame);
    int width = frame.cols/collection.count();
    int offset = 0;
    for(size_t i = 0; i < collection.count() * 2; ++i) {
        drawMatrix(frame, collection[i%collection.count()], rand()%frame.cols, offset, width);
        offset += width;
    }
}

void Glitch_Mirror_Slice_Inc::clear() {
    collection.clear();
}

Glitch_Mirror_Slice_Inc::~Glitch_Mirror_Slice_Inc() {

}

void Glitch_Mirror_Slice_Inc::drawMatrix(cv::Mat &frame, const cv::Mat &src, int off, int x, int w) {
    for(int i = x; i < x+w && i < frame.cols; ++i) {
        int row_size = rsize_val;
        for(int z = 0; z < row_size; ++z) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            if(i + off < frame.cols) {
                 const cv::Vec3b &pix = src.at<cv::Vec3b>(z, off+i);
                for(int q = 0; q < 3; ++q)
                    pixel[q] = ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));
            }
        }
    }
    rsize_val += rand()%100;
    if(rsize_val > frame.rows-10) {
        rsize_val = 0;
    }
}

/* Glitch Mirror Slice Inc_X2 */

void Glitch_Mirror_Slice_Inc_X2::init() {
    size_x = 0;
    rsize_val = 0;
}

void Glitch_Mirror_Slice_Inc_X2::proc(cv::Mat &frame) {
    collection.shiftFrames(frame);
    int width = frame.cols/collection.count();
    int offset = 0;
    for(size_t i = 0; i < collection.count() * 2; ++i) {
        drawMatrix(frame, collection[i%collection.count()], rand()%frame.cols, offset, width);
        offset += width;
    }
}

void Glitch_Mirror_Slice_Inc_X2::clear() {
    collection.clear();
}

Glitch_Mirror_Slice_Inc_X2::~Glitch_Mirror_Slice_Inc_X2() {

}

void Glitch_Mirror_Slice_Inc_X2::drawMatrix(cv::Mat &frame, const cv::Mat &src, int off, int x, int w) {
    for(int i = x; i < x+w && i < frame.cols; ++i) {
        int row_size = rsize_val;
        int row_start = rand()%frame.rows;
        for(int z = row_start; z < row_size; ++z) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            if(i + off < frame.cols) {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, off + i);
                for(int q = 0; q < 3; ++q)
                    pixel[q] = ac::wrap_cast((0.7 * pixel[q]) + (0.5 * pix[q]));
            }
        }
    }
    rsize_val += rand()%100;
    if(rsize_val > frame.rows-10) {
        rsize_val = 0;
    }
}


/* Glitch Mirror Slice X2 */

void Glitch_Mirror_Slice_X2::init() {
    size_x = 0;
    rsize_val = 0;
}

void Glitch_Mirror_Slice_X2::proc(cv::Mat &frame) {
    collection.shiftFrames(frame);
    int width = frame.cols/collection.count();
    int offset = 0;
    for(size_t i = 0; i < collection.count() * 2; ++i) {
        drawMatrix(frame, collection[i%collection.count()], rand()%frame.cols, offset, width);
        offset += width;
    }
}

void Glitch_Mirror_Slice_X2::clear() {
    collection.clear();
}

Glitch_Mirror_Slice_X2::~Glitch_Mirror_Slice_X2() {

}

void Glitch_Mirror_Slice_X2::drawMatrix(cv::Mat &frame, const cv::Mat &src, int off, int x, int w) {
    for(int i = x; i < x+w && i < frame.cols; ++i) {
        int row_size = rsize_val;
        int row_start = rand()%frame.rows;
        for(int z = row_start; z < row_size; ++z) {
            if(frame.cols-i-1 >= 0 && frame.cols-i-1 < frame.cols) {
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, frame.cols-i-1);
                if(i + off < frame.cols) {
                    const cv::Vec3b &pix = src.at<cv::Vec3b>(z, off+i);
                    for(int q = 0; q < 3; ++q)
                        pixel[q] = ac::wrap_cast((0.7 * pixel[q]) + (0.5 * pix[q]));
                }
            }
        }
    }
    rsize_val += rand()%100;
    if(rsize_val > frame.rows-10) {
        rsize_val = 0;
    }
}

/* glitch mirror bars */

void Glitch_Mirror_Bars::init() {
    num_rows = 1;
    dir = 1;
}

void Glitch_Mirror_Bars::proc(cv::Mat &frame) {
    cv::Mat fx = frame.clone();
    for(int i = 0; i < num_rows; ++i) {
        drawMatrix(frame, fx, rand()%2, i,  num_rows);
    }
    if(dir == 1) {
        num_rows += 1;
        if(num_rows >= 32)
            dir = 0;    
    } else {
        num_rows -= 1;
        if(num_rows <= 1)
            dir = 1;
    }
}

void Glitch_Mirror_Bars::clear() {}

Glitch_Mirror_Bars::~Glitch_Mirror_Bars() {}

void Glitch_Mirror_Bars::drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex) {
    int width = frame.cols/sizex;
    int start_x = col*width;
    for(int z = 0; z < frame.rows; ++z) {
        for(int i = start_x; i < start_x+width && i < frame.cols; i++) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            if(rev == 0 && frame.cols-i-1 >= 0 && frame.cols-i-1 < frame.cols) {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, frame.cols-i-1);
                for(int q = 0; q < 3; ++q)
                   pixel[q] = ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));
            } else {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, i);
                for(int q = 0; q < 3; ++q)
                   pixel[q] = ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));
            }
        }
    }
}

/* glitch mirror bars x2*/

void Glitch_Mirror_Bars_X2::init() {
    num_rows = 1;
    dir = 1;
}

void Glitch_Mirror_Bars_X2::proc(cv::Mat &frame) {
    cv::Mat fx = frame.clone();
    for(int i = 0; i < frame.cols/num_rows; ++i) {
        drawMatrix(frame, fx, rand()%2, i,  num_rows);
    }
    if(dir == 1) {
        num_rows += 1;
        if(num_rows >= 128)
            dir = 0;    
    } else {
        num_rows -= 1;
        if(num_rows <= 1)
            dir = 1;
    }
}

void Glitch_Mirror_Bars_X2::clear() {}

Glitch_Mirror_Bars_X2::~Glitch_Mirror_Bars_X2() {}

void Glitch_Mirror_Bars_X2::drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex) {
    int width = sizex;
    int start_x = col*width;
    for(int z = 0; z < frame.rows; ++z) {
        for(int i = start_x; i < start_x+width && i < frame.cols; i++) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            if(rev == 0 && frame.cols-i-1 >= 0 && frame.cols-i-1 < frame.cols) {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, frame.cols-i-1);
                for(int q = 0; q < 3; ++q)
                   pixel[q] = ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));
            } else {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, i);
                for(int q = 0; q < 3; ++q)
                   pixel[q] = ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));
            }
        }
    }
}


/* glitch mirror bars col*/

void Glitch_Mirror_Bars_Col::init() {
    num_rows = 128;
    dir = 1;
}

void Glitch_Mirror_Bars_Col::proc(cv::Mat &frame) {
    collection.shiftFrames(frame);
    for(int i = 0; i < frame.cols/num_rows; ++i) {
        cv::Mat &fx = collection[rand()%collection.count()];
        drawMatrix(frame, fx, 1, i,  num_rows);
    }
    if(dir == 1) {
        num_rows += 1;
        if(num_rows >= 256)
            dir = 0;    
    } else {
        num_rows -= 1;
        if(num_rows <= 128)
            dir = 1;
    }
}

void Glitch_Mirror_Bars_Col::clear() {
    collection.clear();
}

Glitch_Mirror_Bars_Col::~Glitch_Mirror_Bars_Col() {}

void Glitch_Mirror_Bars_Col::drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex) {
    int width = sizex;
    int start_x = col*width;
    for(int z = 0; z < frame.rows; ++z) {
        for(int i = start_x; i < start_x+width && i < frame.cols; i++) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            if(rev == 0 && frame.cols-i-1 >= 0 && frame.cols-i-1 < frame.cols) {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, frame.cols-i-1);
                pixel = pix;
            } else {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, i);
                pixel = pix;
            }
        }
    }
}

/* glitch mirror bars col orig*/

void Glitch_Mirror_Bars_Col_Orig::init() {
    num_rows = 64;
    dir = 1;
}

void Glitch_Mirror_Bars_Col_Orig::proc(cv::Mat &frame) {
    collection.shiftFrames(frame);
    for(int i = 0; i < frame.cols/num_rows; ++i) {
        cv::Mat &fx = collection[rand()%collection.count()];
        drawMatrix(frame, fx, 1, i,  num_rows);
    }
    if(dir == 1) {
        num_rows += 1;
        if(num_rows >= 128)
            dir = 0;    
    } else {
        num_rows -= 1;
        if(num_rows <= 64)
            dir = 1;
    }
}

void Glitch_Mirror_Bars_Col_Orig::clear() {
    collection.clear();
}

Glitch_Mirror_Bars_Col_Orig::~Glitch_Mirror_Bars_Col_Orig() {}

void Glitch_Mirror_Bars_Col_Orig::drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex) {
    int width = sizex;
    int start_x = col*width;
    for(int z = 0; z < frame.rows; ++z) {
        for(int i = start_x; i < start_x+width && i < frame.cols; i++) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            if(rev == 0 && frame.cols-i-1 >= 0 && frame.cols-i-1 < frame.cols) {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, frame.cols-i-1);
                for(int q = 0; q < 3; ++q)
                   pixel[q] = ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));
            } else {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, i);
                for(int q = 0; q < 3; ++q)
                   pixel[q] = ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));
            }
        }
    }
}

/* glitch mirror bars col orig Y*/

void Glitch_Mirror_Bars_Col_OrigY::init() {
    num_rows = 64;
    dir = 1;
}

void Glitch_Mirror_Bars_Col_OrigY::proc(cv::Mat &frame) {
    collection.shiftFrames(frame);
    for(int i = 0; i < frame.cols/num_rows; ++i) {
        cv::Mat &fx = collection[rand()%collection.count()];
        drawMatrix(frame, fx, 1, i,  num_rows);
    }
    if(dir == 1) {
        num_rows += 1;
        if(num_rows >= 128)
            dir = 0;    
    } else {
        num_rows -= 1;
        if(num_rows <= 64)
            dir = 1;
    }
}

void Glitch_Mirror_Bars_Col_OrigY::clear() {
    collection.clear();
}

Glitch_Mirror_Bars_Col_OrigY::~Glitch_Mirror_Bars_Col_OrigY() {}

void Glitch_Mirror_Bars_Col_OrigY::drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex) {
    int width = sizex;
    int start_x = col*width;
    int rand_height = rand()%frame.rows;
    for(int z = 0; z < rand_height; ++z) {
        for(int i = start_x; i < start_x+width && i < frame.cols; i++) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            if(rev == 0 && frame.cols-i-1 >= 0 && frame.cols-i-1 < frame.cols) {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, frame.cols-i-1);
                for(int q = 0; q < 3; ++q)
                   pixel[q] = ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));
            } else {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, i);
                for(int q = 0; q < 3; ++q)
                   pixel[q] = ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));
            }
        }
    }
}

/* glitch mirror bars col orig YH*/

void Glitch_Mirror_Bars_Col_OrigYH::init() {
    num_rows = 64;
    dir = 1;
}

void Glitch_Mirror_Bars_Col_OrigYH::proc(cv::Mat &frame) {
    collection.shiftFrames(frame);
    for(int i = 0; i < frame.cols/num_rows; ++i) {
        cv::Mat &fx = collection[rand()%collection.count()];
        drawMatrix(frame, fx, 1, i,  num_rows);
    }
    if(dir == 1) {
        num_rows += 1;
        if(num_rows >= 128)
            dir = 0;    
    } else {
        num_rows -= 1;
        if(num_rows <= 64)
            dir = 1;
    }
}

void Glitch_Mirror_Bars_Col_OrigYH::clear() {
    collection.clear();
}

Glitch_Mirror_Bars_Col_OrigYH::~Glitch_Mirror_Bars_Col_OrigYH() {}

void Glitch_Mirror_Bars_Col_OrigYH::drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex) {
    int width = sizex;
    int start_x = col*width;
    int rand_height = rand()%frame.rows;
    int rand_start = rand()%frame.rows;
    for(int z = rand_start; z < rand_height; ++z) {
        for(int i = start_x; i < start_x+width && i < frame.cols; i++) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            if(rev == 0 && frame.cols-i-1 >= 0 && frame.cols-i-1 < frame.cols) {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, frame.cols-i-1);
                for(int q = 0; q < 3; ++q)
                   pixel[q] = ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));
            } else {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, i);
                for(int q = 0; q < 3; ++q)
                   pixel[q] = ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));
            }
        }
    }
}

/* glitch mirror bars col orig YH Pixels*/

void Glitch_Mirror_Bars_Col_OrigYH_Pixels::init() {
    num_rows = 64;
    dir = 1;
}

void Glitch_Mirror_Bars_Col_OrigYH_Pixels::proc(cv::Mat &frame) {
    collection.shiftFrames(frame);
    for(int i = 0; i < frame.cols/num_rows; ++i) {
        cv::Mat &fx = collection[rand()%collection.count()];
        drawMatrix(frame, fx, 1, i,  num_rows);
    }
    if(dir == 1) {
        num_rows += 1;
        if(num_rows >= 128)
            dir = 0;    
    } else {
        num_rows -= 1;
        if(num_rows <= 64)
            dir = 1;
    }
}

void Glitch_Mirror_Bars_Col_OrigYH_Pixels::clear() {
    collection.clear();
}

Glitch_Mirror_Bars_Col_OrigYH_Pixels::~Glitch_Mirror_Bars_Col_OrigYH_Pixels() {}

void Glitch_Mirror_Bars_Col_OrigYH_Pixels::drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex) {
    int width = sizex;
    int start_x = col*width;
    int rand_height = rand()%frame.rows;
    int rand_start = rand()%frame.rows;
    for(int z = rand_start; z < rand_height; ++z) {
        for(int i = start_x; i < start_x+width && i < frame.cols; i++) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            if(rev == 0 && frame.cols-i-1 >= 0 && frame.cols-i-1 < frame.cols) {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, frame.cols-i-1);
                for(int q = 0; q < 3; ++q)
                   pixel[q] = ac::wrap_cast((1.1 * pixel[q]) + (1.1 * pix[q]));
            } else {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, i);
                for(int q = 0; q < 3; ++q)
                   pixel[q] = ac::wrap_cast((1.1 * pixel[q]) + (1.1 * pix[q]));
            }
        }
    }
}


/* glitch mirror bars col orig Y*/

void Glitch_Mirror_Bars_Col_OrigY_Grad::init() {
    num_rows = 64;
    dir = 1;
    alpha = 1.0;
}

void Glitch_Mirror_Bars_Col_OrigY_Grad::proc(cv::Mat &frame) {
    collection.shiftFrames(frame);
    for(int i = 0; i < frame.cols/num_rows; ++i) {
        cv::Mat &fx = collection[rand()%collection.count()];
        drawMatrix(frame, fx, 1, i,  num_rows);
    }
    if(dir == 1) {
        num_rows += 1;
        if(num_rows >= 128)
            dir = 0;    
    } else {
        num_rows -= 1;
        if(num_rows <= 64)
            dir = 1;
    }

    if(alpha_dir == 1) {
        alpha += 0.05;
        if(alpha >= 1.0) {
            alpha_dir = 0;
        }
    } else {
        alpha -= 0.05;
        if(alpha <= 0.1) {
            alpha_dir = 1;
        }
    }
}

void Glitch_Mirror_Bars_Col_OrigY_Grad::clear() {
    collection.clear();
}

Glitch_Mirror_Bars_Col_OrigY_Grad::~Glitch_Mirror_Bars_Col_OrigY_Grad() {}

void Glitch_Mirror_Bars_Col_OrigY_Grad::drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex) {
    int width = sizex;
    int start_x = col*width;
    int rand_height = rand()%frame.rows;
    for(int z = 0; z < rand_height; ++z) {
        for(int i = start_x; i < start_x+width && i < frame.cols; i++) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            if(rev == 0 && frame.cols-i-1 >= 0 && frame.cols-i-1 < frame.cols) {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, frame.cols-i-1);
                for(int q = 0; q < 3; ++q)
                   pixel[q] = ac::wrap_cast((alpha * pixel[q]) + ((1-alpha) * pix[q]));
            } else {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, i);
                for(int q = 0; q < 3; ++q)
                   pixel[q] = ac::wrap_cast((alpha * pixel[q]) + ((1-alpha) * pix[q]));
            }
        }
    }
}

/* glitch mirror bars col orig Y grad overflow*/

void Glitch_Mirror_Bars_Col_OrigY_Grad_Overflow::init() {
    num_rows = 64;
    dir = 1;
    alpha = 1.0;
}

void Glitch_Mirror_Bars_Col_OrigY_Grad_Overflow::proc(cv::Mat &frame) {
    collection.shiftFrames(frame);
    for(int i = 0; i < frame.cols/num_rows; ++i) {
        cv::Mat &fx = collection[rand()%collection.count()];
        drawMatrix(frame, fx, 1, i,  num_rows);
    }
    if(dir == 1) {
        num_rows += 1;
        if(num_rows >= 128)
            dir = 0;    
    } else {
        num_rows -= 1;
        if(num_rows <= 64)
            dir = 1;
    }

    if(alpha_dir == 1) {
        alpha += 0.05;
        if(alpha >= 3.0) {
            alpha_dir = 0;
        }
    } else {
        alpha -= 0.05;
        if(alpha <= 0.1) {
            alpha_dir = 1;
        }
    }
}

void Glitch_Mirror_Bars_Col_OrigY_Grad_Overflow::clear() {
    collection.clear();
}

Glitch_Mirror_Bars_Col_OrigY_Grad_Overflow::~Glitch_Mirror_Bars_Col_OrigY_Grad_Overflow() {}

void Glitch_Mirror_Bars_Col_OrigY_Grad_Overflow::drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex) {
    int width = sizex;
    int start_x = col*width;
    int rand_height = rand()%frame.rows;
    for(int z = 0; z < rand_height; ++z) {
        for(int i = start_x; i < start_x+width && i < frame.cols; i++) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            if(rev == 0 && frame.cols-i-1 >= 0 && frame.cols-i-1 < frame.cols) {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, frame.cols-i-1);
                for(int q = 0; q < 3; ++q)
                   pixel[q] = ac::wrap_cast((alpha * pixel[q]) + ((1-alpha) * pix[q]));
            } else {
                const cv::Vec3b &pix = src.at<cv::Vec3b>(z, i);
                for(int q = 0; q < 3; ++q)
                   pixel[q] = ac::wrap_cast((alpha * pixel[q]) + ((1-alpha) * pix[q]));
            }
        }
    }
}

/* glitch mirror bars horiz */

void Glitch_Mirror_Bars_Horiz::init() {
    num_rows = 25;
    height = 23;
    dir = 1;
}
void Glitch_Mirror_Bars_Horiz::proc(cv::Mat &frame) {
    num_rows = frame.rows/height;

    collection.shiftFrames(frame);
    for(int i = 0; i < num_rows; ++i) {
        drawMatrixRect(frame, collection[rand()%collection.count()], i*height, height);
    }

    if(dir == 1) {
        height += 5;
        if(height >= frame.rows/2) {
            dir = 0;
        }
    } else {
        dir -= 5;
        if(height <= 5) {
            dir = 1;
        }
    }
}

void Glitch_Mirror_Bars_Horiz::clear() {
    collection.clear();
}
Glitch_Mirror_Bars_Horiz::~Glitch_Mirror_Bars_Horiz() {}


void Glitch_Mirror_Bars_Horiz::drawMatrixRect(cv::Mat &frame, const cv::Mat &src, int row, int height) {
    int start_y = row;
    for(int y = start_y; y < start_y+height && y < frame.rows; ++y) {
        for(int x = 0; x < frame.cols; ++x) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
            const cv::Vec3b &pix = src.at<cv::Vec3b>(y, x);
            for(int q = 0; q < 3; ++q) 
                pixel[q] = ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));

        }
    }
}

/* glitch mirror bars horiz x1 */

void Glitch_Mirror_Bars_Horiz_X1::init() {
    num_rows = 25;
    height = 23;
    dir = 1;
}
void Glitch_Mirror_Bars_Horiz_X1::proc(cv::Mat &frame) {
    num_rows = frame.rows/height;

    collection.shiftFrames(frame);
    for(int i = 0; i < num_rows; ++i) {
        drawMatrixRect(frame, collection[rand()%collection.count()], i*height, height);
    }

    if(dir == 1) {
        height += 2;
        if(height >= frame.rows/4) {
            dir = 0;
        }
    } else {
        dir -= 2;
        if(height <= 5) {
            dir = 1;
        }
    }
}

void Glitch_Mirror_Bars_Horiz_X1::clear() {
    collection.clear();
}
Glitch_Mirror_Bars_Horiz_X1::~Glitch_Mirror_Bars_Horiz_X1() {}


void Glitch_Mirror_Bars_Horiz_X1::drawMatrixRect(cv::Mat &frame, const cv::Mat &src, int row, int height) {
    int start_y = row;
    for(int y = start_y; y < start_y+height && y < frame.rows; ++y) {
        for(int x = 0; x < frame.cols; ++x) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
            const cv::Vec3b &pix = src.at<cv::Vec3b>(y, x);
            for(int q = 0; q < 3; ++q) 
                pixel[q] = ac::wrap_cast((0.5 * pixel[q]) + (0.5 * pix[q]));

        }
    }
}

/* glitch mirror bars horiz x1 grad*/

void Glitch_Mirror_Bars_Horiz_X1_Grad::init() {
    num_rows = 25;
    height = 23;
    dir = 1;
    alpha = 0.1;
    alpha_dir = 1;
}
void Glitch_Mirror_Bars_Horiz_X1_Grad::proc(cv::Mat &frame) {
    num_rows = frame.rows/height;

    collection.shiftFrames(frame);
    for(int i = 0; i < num_rows; ++i) {
        drawMatrixRect(frame, collection[rand()%collection.count()], i*height, height);
    }

    if(dir == 1) {
        height += 2;
        if(height >= frame.rows/4) {
            dir = 0;
        }
    } else {
        dir -= 2;
        if(height <= 5) {
            dir = 1;
        }
    }

    if(alpha_dir == 1) {
        alpha += 0.05;
        if(alpha >= 1.0) {
            alpha_dir = 0;
        }
    } else {
        alpha -= 0.05;
        if(alpha <= 0.1) {
            alpha_dir = 1;
        }
    }
}

void Glitch_Mirror_Bars_Horiz_X1_Grad::clear() {
    collection.clear();
}
Glitch_Mirror_Bars_Horiz_X1_Grad::~Glitch_Mirror_Bars_Horiz_X1_Grad() {}


void Glitch_Mirror_Bars_Horiz_X1_Grad::drawMatrixRect(cv::Mat &frame, const cv::Mat &src, int row, int height) {
    int start_y = row;
    for(int y = start_y; y < start_y+height && y < frame.rows; ++y) {
        for(int x = 0; x < frame.cols; ++x) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
            const cv::Vec3b &pix = src.at<cv::Vec3b>(y, x);
            for(int q = 0; q < 3; ++q) 
                pixel[q] = ac::wrap_cast((alpha * pixel[q]) + ((1-alpha) * pix[q]));

        }
    }
}

/* glitch mirror bars horiz x1 grad xor*/

void Glitch_Mirror_Bars_Horiz_X1_Grad_Xor::init() {
    num_rows = 25;
    height = 23;
    dir = 1;
    alpha = 0.1;
    alpha_dir = 1;
}
void Glitch_Mirror_Bars_Horiz_X1_Grad_Xor::proc(cv::Mat &frame) {
    num_rows = frame.rows/height;

    collection.shiftFrames(frame);
    for(int i = 0; i < num_rows; ++i) {
        drawMatrixRect(frame, collection[rand()%collection.count()], i*height, height);
    }

    if(dir == 1) {
        height += 2;
        if(height >= frame.rows/4) {
            dir = 0;
        }
    } else {
        dir -= 2;
        if(height <= 5) {
            dir = 1;
        }
    }

    if(alpha_dir == 1) {
        alpha += 0.05;
        if(alpha >= 1.0) {
            alpha_dir = 0;
        }
    } else {
        alpha -= 0.05;
        if(alpha <= 0.1) {
            alpha_dir = 1;
        }
    }
}

void Glitch_Mirror_Bars_Horiz_X1_Grad_Xor::clear() {
    collection.clear();
}
Glitch_Mirror_Bars_Horiz_X1_Grad_Xor::~Glitch_Mirror_Bars_Horiz_X1_Grad_Xor() {}


void Glitch_Mirror_Bars_Horiz_X1_Grad_Xor::drawMatrixRect(cv::Mat &frame, const cv::Mat &src, int row, int height) {
    int start_y = row;
    for(int y = start_y; y < start_y+height && y < frame.rows; ++y) {
        for(int x = 0; x < frame.cols; ++x) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
            const cv::Vec3b &pix = src.at<cv::Vec3b>(y, x);
            for(int q = 0; q < 3; ++q) 
                pixel[q] ^= ac::wrap_cast((alpha * pixel[q]) + ((1-alpha) * pix[q]));

        }
    }
}

/* line horiz */

void Glitch_Line_Horiz::init() {
    offset_y = rand()%300;
    color = cv::Vec3b(150, 150, 150);
}

void Glitch_Line_Horiz::proc(cv::Mat &frame) {
    for(int x = 0; x < frame.cols; ++x) {
        color = cv::Vec3b(rand()%255, rand()%255, rand()%255);
        const cv::Vec3b &pix = frame.at<cv::Vec3b>(rand()%(frame.rows/2), x);
        for(int y = 0; y < offset_y && y < frame.rows; ++y) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
            pixel[0] += pix[0]^pixel[0]*color[0];
            pixel[1] += pix[1]^pixel[1]*color[1];
            pixel[2] += pix[2]^pixel[2]*color[2];
        }
        offset_y = rand()%frame.rows;
    }
}

void Glitch_Line_Horiz::clear() {}

Glitch_Line_Horiz::~Glitch_Line_Horiz() {}

/* line horiz grad (alpha) */

void Glitch_Line_Horiz_Grad::init() {
    offset_y = rand()%300;
    color = cv::Vec3b(150, 150, 150);
    alpha_dir = 1;
    alpha = 0.5;
}

void Glitch_Line_Horiz_Grad::proc(cv::Mat &frame) {
    for(int x = 0; x < frame.cols; ++x) {
        color = cv::Vec3b(rand()%255, rand()%255, rand()%255);
        const cv::Vec3b &pix = frame.at<cv::Vec3b>(rand()%(frame.rows/2), x);
        for(int y = 0; y < offset_y && y < frame.rows; ++y) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
            pixel[0] = ac::wrap_cast((alpha * pixel[0]) + ((1-alpha) * (pix[0]^pixel[0]*color[0])));
            pixel[1] = ac::wrap_cast((alpha * pixel[1]) + ((1-alpha) * (pix[1]^pixel[1]*color[1])));
            pixel[2] = ac::wrap_cast((alpha * pixel[2]) + ((1-alpha) * (pix[2]^pixel[2]*color[2])));
        }
        offset_y = rand()%frame.rows;
    }

     if(alpha_dir == 1) {
        alpha += 0.05;
        if(alpha >= 1.0) {
            alpha_dir = 0;
        }
    } else {
        alpha -= 0.05;
        if(alpha <= 0.1) {
            alpha_dir = 1;
        }
    }
}

void Glitch_Line_Horiz_Grad::clear() {}

Glitch_Line_Horiz_Grad::~Glitch_Line_Horiz_Grad() {}

/* glitch rect grad */

void Glitch_Rect_Grad::init() {
    num_rows = 8;
    num_cols = 8;
    arr_size = num_rows * num_cols;
    alpha_array = new double[ arr_size ];
    for(int i = 0; i < arr_size; ++i) {
        alpha_array[i] = (0.1) * (rand()%10);
    }
}

void Glitch_Rect_Grad::proc(cv::Mat &frame) {

    collection.shiftFrames(frame);

    int row_size = frame.rows/num_rows;
    int col_size = frame.cols/num_cols;
    int index = 0;

    for(int y = 0; y < frame.rows; y += row_size) {
        for(int x = 0; x < frame.cols; x += col_size) {
            drawBlock(alpha_array[index++], x, y, col_size, row_size, frame, collection[rand()%collection.count()]);
        }   
    }

    for(int i = 0; i < index; ++i) {
        alpha_array[i] += 0.05;
        if(alpha_array[i] >= 1.0)
            alpha_array[i] = 0.1;
    }
}

void Glitch_Rect_Grad::drawBlock(double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src) {
    for(int z = y; z < y+h && z < frame.rows; ++z) {
        for(int i = x;  i < x+w && i < frame.cols; ++i) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            const cv::Vec3b &pix = src.at<cv::Vec3b>(z, i);
            for(int q = 0; q < 3; ++q)
                pixel[q] = ac::wrap_cast((alpha * pixel[q]) + ((1-alpha)*pix[q]));
        }
    }
}

void Glitch_Rect_Grad::clear() {
    collection.clear();
}


Glitch_Rect_Grad::~Glitch_Rect_Grad() {}