#ifndef CAT_VEC_H_
#define CAT_VEC_H_

#include<vector>
#include<string>
#include<unordered_map>
#include<fstream>
#include<iostream>

extern std::vector<std::string> cat_in_order, cat_sorted, cat_fast, cat_glitch, cat_mirror;
extern std::vector<std::string> *vec_cat[];

struct ColorType {
    unsigned char red = 0;
    unsigned char green = 0;
    unsigned char blue = 0;
    bool off = false;
    ColorType() : red{0}, green{0}, blue{0} {}
    ColorType(unsigned char &r, unsigned char &g, unsigned char &b) : red{r}, green{g}, blue{b} {}
    ColorType(const ColorType &c) : red{c.red}, green{c.green}, blue{c.blue} {}
    ColorType &operator=(const ColorType &c) {
        red = c.red;
        green = c.green;
        blue = c.blue;
        return *this;
    }
    void clear() { red = green = blue = 0; }
    void set(unsigned char r, unsigned char g, unsigned char b) {
        red = r;
        green = g;
        blue = b;
    }

    std::string getColorValue() {
        std::string value = "";
        if(red) 
            value += "R";
        if(green)
            value += "G";
        if(blue)
            value += "B";
        return value;
    }
};

class Custom_Filter {
public:
    std::string name, color_values;
    ColorType color;
    Custom_Filter(const std::string &n) {
        // convert n to name/colortype
        if(n.find(":") == std::string::npos || n.find("Custom__") != std::string::npos) {
            color.off = true;
            name = n;
        } else {
            name = n;//.substr(0, n.find(";"));
            std::string colors = n.substr(n.find(":")+1, n.length());
            if(colors.length() == 0) {
                color.off = true;
                return;
            }
            color_values = colors;
            if(colors.find("B") != std::string::npos) {
                color.blue = 1;
            } 
            if(colors.find("G") != std::string::npos) {
                color.green = 1;
            }
            if(colors.find("R") != std::string::npos) {
                color.red = 1;
            }
        }
    }
};

using custom_filter = std::pair<std::string, std::vector<Custom_Filter>>;
extern std::vector<custom_filter> cat_custom;
extern std::unordered_map<std::string, int> cat_custom_index;
extern std::vector<std::string> cat_playlist;
extern std::unordered_map<std::string, int> cat_playlist_index;
void build_lists(std::string filename);
void load_custom(std::string filename);
void save_custom(std::string filename);
void load_playlist(std::string filename);
void save_playlist(std::string filename);
void clear_custom();
bool custom_exists(const std::string &s);
void custom_setup_map(bool clear);
int count_filters();


#endif