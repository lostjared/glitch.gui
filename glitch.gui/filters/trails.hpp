#ifndef _TRAILS_H__
#define _TRAILS_H__

#include "../new_filter.hpp"

class SimpleTrails : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    ~SimpleTrails();
private:
    FrameCollection collection;

};



#endif