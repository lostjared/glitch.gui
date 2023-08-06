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

#endif
