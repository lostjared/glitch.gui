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

class ColorXor3 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    ~ColorXor3();
private:
   double alpha[3];
   int dir[3];
   double max_x[3]= {1.0, 2.0, 3.0};
   double min_x[3] = {3.0, 2.0, 1.0};   
};

class ColorXor4 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    ~ColorXor4();
private:
    double alpha[3];
    int dir[3];
    double max_x = 1.0, min_x = 1.0;
};

class ColorXor5 : public FilterFunc {
public:
    void init() override;
    void proc(cv::Mat &frame) override;
    ~ColorXor5();
private:
    double alpha[3];
    int dir[3];
};

#endif