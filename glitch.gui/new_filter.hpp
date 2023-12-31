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
#endif
