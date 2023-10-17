#ifndef _GLITCH_H__
#define _GLITCH_H__


#include "../new_filter.hpp"

class Glitch_Line_Down : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Line_Down();
private:
    int offset_y;
    cv::Vec3b color;
};

class Glitch_Line_Down_X2 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Line_Down_X2();
private:
    int offset_y;
    cv::Vec3b color;
};

class Glitch_Line_Down_X3 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Line_Down_X3();
private:
    int offset_y;
    cv::Vec3b color;
    
};

class Glitch_Line_Down_X4 : public FilterFunc {
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Line_Down_X4();
private:
    int offset_y;
    cv::Vec3b color;
};

class Glitch_Line_Down_X5 : public FilterFunc {
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Line_Down_X5();
private:
    int offset_y;
    cv::Vec3b color;
};

class Glitch_RandRect : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_RandRect();
private:
    void blendRect(cv::Mat &frame, cv::Vec3b &color, int x, int y, int w, int h);
};

class Glitch_RandRect_X2 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_RandRect_X2();
private:
    void blendRect(cv::Mat &frame, cv::Vec3b &color, int x, int y, int w, int h);
};

class Glitch_RandRect_X2_Wrap : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_RandRect_X2_Wrap();
private:
    void blendRect(cv::Mat &frame, cv::Vec3b &color, int x, int y, int w, int h);
};

class Glitch_RandRect_X3 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_RandRect_X3();
private:
    void blendRect(cv::Mat &frame, cv::Vec3b &color, int x, int y, int w, int h);
};

class Glitch_RandRect_X4 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_RandRect_X4();
private:
    void blendRect(cv::Mat &frame, cv::Vec3b &color,cv::Vec3b &color2, int x, int y, int w, int h);
};

class Glitch_Pixel_X1 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Pixel_X1();
private:
    void fillRect(cv::Mat &frame, int x, int y, int w, int h);
};

class Glitch_Mirror_Shift : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Shift();
private:
    void drawMatrix(cv::Mat &frame, const cv::Mat &src, int off, int x, int w);
    FrameCollection collection;
    int size_x;
};

class Glitch_Mirror_Shift_Xor : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Shift_Xor();
private:
    void drawMatrix(cv::Mat &frame, const cv::Mat &src, int off, int x, int w);
    FrameCollection collection;
    int size_x;
};

class Glitch_Mirror_Slice : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Slice();
private:
    void drawMatrix(cv::Mat &frame, const cv::Mat &src, int off, int x, int w);
    FrameCollection collection;
    int size_x;
};

class Glitch_Mirror_Slice_Rand : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Slice_Rand();
private:
    void drawMatrix(cv::Mat &frame, const cv::Mat &src, int off, int x, int w);
    FrameCollection collection;
    int size_x;
};

class Glitch_Mirror_Slice_Inc : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Slice_Inc();
private:
    void drawMatrix(cv::Mat &frame, const cv::Mat &src, int off, int x, int w);
    FrameCollection collection;
    int size_x;
    int rsize_val;
};


class Glitch_Mirror_Slice_Inc_X2 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Slice_Inc_X2();
private:
    void drawMatrix(cv::Mat &frame, const cv::Mat &src, int off, int x, int w);
    FrameCollection collection;
    int size_x;
    int rsize_val;
};

class Glitch_Mirror_Slice_X2 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Slice_X2();
private:
    void drawMatrix(cv::Mat &frame, const cv::Mat &src, int off, int x, int w);
    FrameCollection collection;
    int size_x;
    int rsize_val;
};

class Glitch_Mirror_Bars : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Bars();
private:
    void drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex);
    int num_rows, dir;
};

class Glitch_Mirror_Bars_X2 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Bars_X2();
private:
    void drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex);
    int num_rows, dir;
};

class Glitch_Mirror_Bars_Col : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Bars_Col();
private:
    void drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex);
    int num_rows, dir;
    FrameCollection collection;
};

class Glitch_Mirror_Bars_Col_Orig : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Bars_Col_Orig();
private:
    void drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex);
    int num_rows, dir;
    FrameCollection collection;
};

class Glitch_Mirror_Bars_Col_OrigY : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Bars_Col_OrigY();
private:
    void drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex);
    int num_rows, dir;
    FrameCollection collection;
};

class Glitch_Mirror_Bars_Col_OrigYH : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Bars_Col_OrigYH();
private:
    void drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex);
    int num_rows, dir;
    FrameCollection collection;
};

class Glitch_Mirror_Bars_Col_OrigYH_Pixels : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Bars_Col_OrigYH_Pixels();
private:
    void drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex);
    int num_rows, dir;
    FrameCollection collection;
};

class Glitch_Mirror_Bars_Col_OrigY_Grad : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Bars_Col_OrigY_Grad();
private:
    void drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex);
    int num_rows, dir;
    double alpha = 1.0;
    int alpha_dir = 1;
    FrameCollection collection;
};

class Glitch_Mirror_Bars_Col_OrigY_Grad_Overflow : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Bars_Col_OrigY_Grad_Overflow();
private:
    void drawMatrix(cv::Mat &frame, const cv::Mat &src, int rev, int col, int sizex);
    int num_rows, dir;
    double alpha = 1.0;
    int alpha_dir = 1;
    FrameCollection collection;
};

class Glitch_Mirror_Bars_Horiz : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Bars_Horiz();
private:
    void drawMatrixRect(cv::Mat &frame, const cv::Mat &src, int row, int height);
    FrameCollection collection;
    int num_rows, height, dir;
};

class Glitch_Mirror_Bars_Horiz_X1 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Bars_Horiz_X1();
private:
    void drawMatrixRect(cv::Mat &frame, const cv::Mat &src, int row, int height);
    FrameCollection collection;
    int num_rows, height, dir;
};

class Glitch_Mirror_Bars_Horiz_X1_Grad : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Bars_Horiz_X1_Grad();
private:
    void drawMatrixRect(cv::Mat &frame, const cv::Mat &src, int row, int height);
    FrameCollection collection;
    int num_rows, height, dir, alpha_dir;
    double alpha;
};

class Glitch_Mirror_Bars_Horiz_X1_Grad_Xor : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Mirror_Bars_Horiz_X1_Grad_Xor();
private:
    void drawMatrixRect(cv::Mat &frame, const cv::Mat &src, int row, int height);
    FrameCollection collection;
    int num_rows, height, dir, alpha_dir;
    double alpha;
};

class Glitch_Line_Horiz : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Line_Horiz();
private:
    int offset_y;
    cv::Vec3b color;
};

class Glitch_Line_Horiz_Grad : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Line_Horiz_Grad();
private:
    int offset_y;
    cv::Vec3b color;
    double alpha;
    int alpha_dir;
};

class Glitch_Rect_Grad : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_Grad();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int arr_size;
    double *alpha_array = nullptr;
    void drawBlock(double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);

};

class Glitch_Rect_Size : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_Size();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    void drawBlock(double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};

class Glitch_Rect_SizeY : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_SizeY();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    void drawBlock(double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};

class Glitch_Rect_SizeX: public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_SizeX();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    void drawBlock(double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};

class Glitch_Rect_Size_Odd: public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_Size_Odd();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    void drawBlock(double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};

class Glitch_Rect_Size_Overflow : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_Size_Overflow();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    void drawBlock(double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};

class Glitch_Rect_Size_Fast : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_Size_Fast();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    void drawBlock(double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};

class Glitch_Rect_Size_Slow : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_Size_Slow();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    void drawBlock(double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};

class Glitch_Rect_Size_Row : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_Size_Row();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    size_t index;
    void drawBlock(double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};

class Glitch_Rect_Size_Row_Rand : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_Size_Row_Rand();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    void drawBlock(double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};

class Glitch_Rect_Size_RGB : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_Size_RGB();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    void drawBlock(int channel, double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};

class Glitch_Rect_Size_RGB_Order : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_Size_RGB_Order();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    void drawBlock(int channel, double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};

class Glitch_Rect_Size_Col : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_Size_Col();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    size_t index;
    void drawBlock(double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};

class Glitch_Rect_Size_Rev : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_Size_Rev();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    void drawBlock(double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};

class Glitch_Rect_Size_Xor : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_Size_Xor();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    void drawBlock(double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};

class Glitch_Rect_Size_Fade : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_Size_Fade();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    void drawBlock(int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};


class Glitch_Line_Effect : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Line_Effect();
private:
    char col;
    double alpha;
};

class Glitch_Line_Effect_Down : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Line_Effect_Down();
private:
    double alpha;
};

class Glitch_Rect_Size_Rand : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_Size_Rand();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    void drawBlock(double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};

class Glitch_Rect_Size_V2 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Rect_Size_V2();
private:
    FrameCollection collection;
    int num_rows;
    int num_cols;
    int num_dir;
    void drawBlock(double &alpha, int x, int y,  int w, int h, cv::Mat &frame, const cv::Mat &src);
};

class Glitch_Line_Effect_Down_V2 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Line_Effect_Down_V2();
private:
    double alpha;
};

class Glitch_Line_Effect_Down_V3 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Line_Effect_Down_V3();
private:
    double alpha;
    FrameCollection collection;
};

class Glitch_Line_Effect_Down_V4 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Line_Effect_Down_V4();
private:
    double alpha;
    FrameCollection collection;
};

class Glitch_Line_Effect_Down_V5 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Line_Effect_Down_V5();
private:
    double alpha;
    FrameCollection collection;
    size_t index;
};

class Glitch_Line_Effect_Down_V5_Strong : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    void clear() override;
    ~Glitch_Line_Effect_Down_V5_Strong();
private:
    double alpha;
    FrameCollection collection;
    size_t index;
};


#endif
