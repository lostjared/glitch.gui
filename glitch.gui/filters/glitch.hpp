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

};



#endif