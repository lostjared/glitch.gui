#include"new_filter.hpp"
#include<unordered_map>

std::vector<FilterList> new_filter_list;
std::unordered_map<std::string, FilterList*> new_filter_map;

class ColorXor1 : public FilterFunc {
public:
    double alpha[3];
    int dir[3];
    
    void init() override {
        srand(static_cast<unsigned int>(time(0)));
        alpha[0] = static_cast<double>(rand()%4);
        alpha[1] = static_cast<double>(rand()%4);
        alpha[2] = static_cast<double>(rand()%4);
        dir[0] = rand()%2;
        dir[1] = rand()%2;
        dir[2] = rand()%2;
    }
    ~ColorXor1() {
        // release
        std::cout << "release..\n";
    }
    void proc(cv::Mat &frame) override {
        for(int z = 0; z < frame.rows; z++) {
            for(int i = 0; i < frame.cols; i++) {
                cv::Vec3b &pixel = ac::pixelAt(frame, z, i);
                unsigned char value[3];
                for(int q = 0; q < 3; ++q) {
                    value[q] = ac::wrap_cast(alpha[q] * pixel[q]);
                    pixel[q] = pixel[q]^value[q];
                }
            }
        }
        for(int q = 0; q < 3; ++q) {
            if(dir[q] == 1) {
                alpha[q] += 0.1;
                if(alpha[q] >= 3.0) {
                    alpha[q] = 3.0;
                    dir[q] = 0;
                }
            } else {
                alpha[q] -= 0.1;
                if(alpha[q] <= 1) {
                    alpha[q] = 1.0;
                    dir[q] = 1;
                }
            }
        }
    }
};

void init_filter_list() {
    new_filter_list.push_back({"New_ColorXor1", new ColorXor1()});
    
}

// if need to be released
void release_filter_list() {
    for(int i = 0; i < static_cast<int>(new_filter_list.size()); ++i) {
        delete new_filter_list[i].filter;
    }
}


void update_new_filter_map() {
    for(int i = 0; i < static_cast<int>(new_filter_list.size()); ++i) {
        new_filter_map[new_filter_list[i].name] = &new_filter_list[i];
    }
}

void add_new_filter(const FilterList &lst) {
    new_filter_list.push_back(lst);
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

void New_CallFilterClear(std::string name) {
    if(name.find("New_") == std::string::npos) {
        return;
    } else {
        auto pos = new_filter_map.find(name);
        if(pos != new_filter_map.end()) {
            FilterList *l = pos->second;
            l->filter->clear();
        }
    }
}
