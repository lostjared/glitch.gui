#include"new_filter.hpp"


std::vector<FilterList> new_filter_list;

class ColorXor1 : public FilterFunc {
public:
    void init() override {

    }
    void free() override {

    }
    void proc(cv::Mat &frame) override {

    }
};

void init_filter_list() {
    static ColorXor1 color_xor1;
    new_filter_list.push_back( {"ColorXor1", &color_xor1});
}