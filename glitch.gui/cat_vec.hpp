#ifndef CAT_VEC_H_
#define CAT_VEC_H_

#include<vector>
#include<string>

extern std::vector<std::string> cat_in_order, cat_sorted, cat_fast, cat_glitch, cat_mirror;
extern std::vector<std::string> *vec_cat[];

using custom_filter = std::pair<std::string, std::vector<std::string>>;
extern std::vector<custom_filter> cat_custom;

void build_lists();

#endif