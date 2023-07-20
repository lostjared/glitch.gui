#ifndef _NEW_FILTER_H_
#define _NEW_FILTER_H_

#include"acidcam/ac.h"
#include<vector>

class FilterFunc {
    public:
    virtual ~FilterFunc() = default;
    virtual void init() = 0;
    virtual void free() = 0;
    virtual void proc(cv::Mat &frame) = 0;
};

struct FilterList {
    const char *name;
    FilterFunc *filter;
};

extern std::vector<FilterList> new_filter_list;
void init_filter_list();

#endif