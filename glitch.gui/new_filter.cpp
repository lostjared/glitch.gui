#include"new_filter.hpp"
#include<unordered_map>


std::vector<FilterList> new_filter_list;
std::unordered_map<std::string, FilterList*> new_filter_map;

class ColorXor1 : public FilterFunc {
public:
    void init() override {

    }
    ~ColorXor1() {
        // release
        std::cout << "release..\n";
    }
    void proc(cv::Mat &frame) override {
    }
};

void init_filter_list() {
    static ColorXor1 color_xor1;
    new_filter_list.push_back( {"New_ColorXor1", &color_xor1});
    for(int i = 0; i < static_cast<int>(new_filter_list.size()); ++i) {
        new_filter_map[new_filter_list[i].name] = &new_filter_list[i];
    }
}

void New_CallFilter(std::string name, cv::Mat &frame) {

    if(name.find("New_") == std::string::npos) {
        ac::CallFilter(name, frame);
    } else {
        auto pos = new_filter_map.find(name);
        if(pos != new_filter_map.end()) {
            FilterList *l = pos->second;
            if(l->filter->init_ == false) {
                l->filter->init();
                l->filter->init_ = true;
            }
            l->filter->proc(frame);
        }
    }
}