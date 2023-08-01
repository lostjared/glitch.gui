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

#endif