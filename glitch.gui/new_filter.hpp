#ifndef _NEW_FILTER_H_
#define _NEW_FILTER_H_

#include"acidcam/ac.h"
#include<vector>
#include"filters/frame_collection.hpp"

class FilterFunc {
public:
    virtual ~FilterFunc() = default;
    virtual void init() = 0;
    virtual void proc(cv::Mat &frame) = 0;
    virtual void clear() { }  
    bool init_ = false;
    void operator()(cv::Mat &frame) {
        proc(frame);
    }
};

struct FilterList {
    const char *name;
    FilterFunc *filter;
};

extern std::vector<FilterList> new_filter_list;
void init_filter_list();
void add_new_filter(const FilterList &lst);
void update_new_filter_map();
void release_filter_list();
void New_CallFilter(std::string name, cv::Mat &frame);
void New_CallFilterClear(std::string name);
void Plug_CallFilterClear(std::string name);

template<typename T>
void setvec(T &dst, const T &src) {
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

#endif
