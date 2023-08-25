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

#endif
