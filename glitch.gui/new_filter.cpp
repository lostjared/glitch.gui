#include"new_filter.hpp"
#include"cat_vec.hpp"
#include<unordered_map>
#include"plugin_program.hpp"
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
    
    ~ColorXor1() {}

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


void New_CallReplace(const std::string &name,cv::Mat &frame,ColorType &c) {
    if(c.off == true) {
        New_CallFilter(name, frame);
        return;
    }
    std::vector<cv::Mat> origCh(3), procCh(3);
    cv::split(frame, origCh);  
    New_CallFilter(name, frame); 
    cv::split(frame, procCh); 
    if(c.red == 1) {
        procCh[2] = origCh[2];  
    }
    if(c.green == 1)
        procCh[1] = origCh[1];
    if(c.blue == 1)
        procCh[0] = origCh[0];
    cv::merge(procCh, frame); 
}


void New_CallFilter(std::string name, cv::Mat &frame) {

    if(name.find(".acidcam")  != std::string::npos) {

        auto fptr = plug_map.find(name);
        if(fptr == plug_map.end()) {
            std::cerr << "Error: " << name << " not found\n";
        }
         else {
            int index = fptr->second;
            Plugin_Program *prog = plugins[index].second;
            if(prog->init == false) {
                prog->f_init();
                prog->init = true;
            }           
            prog->f_proc(frame);
         }
    } else if(name.find("Custom__") != std::string::npos) {
        int index = cat_custom_index[name];
        auto &lst = cat_custom[index].second;
        for(size_t i = 0; i < lst.size(); ++i) {
            std::string &name_index = lst[i].name;
            auto cpos = name_index.find(":");
            if(cpos != std::string::npos)
                name_index = name_index.substr(0, cpos);

            ColorType &c = lst[i].color;
            New_CallReplace(name_index, frame, c); 
        }
    } else if(name.find("New_") == std::string::npos) {
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
    if(name.find(".acidcam") != std::string::npos) {
        auto fptr = plug_map.find(name);
        if(fptr == plug_map.end()) {
            std::cerr << "Error: " << name << " not found\n";
        }
         else {
            int index = fptr->second;
            Plugin_Program *prog = plugins[index].second;
            if(prog->init == true) {
                prog->f_clear();
            }
         }
    } 
    else
    if(name.find("New_") != std::string::npos) {
        auto pos = new_filter_map.find(name);
        if(pos != new_filter_map.end()) {
            FilterList *l = pos->second;
            if(l->filter->init_ == true)
                l->filter->clear();
        }
    } else if(name.find("Custom_") != std::string::npos) {
        int index = cat_custom_index[name];
        auto &lst = cat_custom[index].second;
        for(size_t i = 0; i < lst.size(); ++i) {
            std::string &name_index = lst[i].name;
            New_CallFilterClear(name_index); 
        } 
    }
}
