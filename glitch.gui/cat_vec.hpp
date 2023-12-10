#ifndef CAT_VEC_H_
#define CAT_VEC_H_

#include<vector>
#include<string>
#include<unordered_map>

extern std::vector<std::string> cat_in_order, cat_sorted, cat_fast, cat_glitch, cat_mirror;
extern std::vector<std::string> *vec_cat[];

using custom_filter = std::pair<std::string, std::vector<std::string>>;
extern std::vector<custom_filter> cat_custom;
extern std::unordered_map<std::string, int> cat_custom_index;
void build_lists();
void save_custom();
bool custom_exists(const std::string &s);
void setup_map(bool clear);
#endif