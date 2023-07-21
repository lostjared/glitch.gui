#ifndef __COLOR_XOR_2_HPP
#define __COLOR_XOR_2_HPP

#include"../new_filter.hpp"

class ColorXor2 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    ~ColorXor2();
private:
    double alpha[3];
    int dir[3];
    
};


#endif