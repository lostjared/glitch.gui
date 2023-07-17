#include"cat_vec.hpp"
#include"acidcam/ac.h"

#include<algorithm>

std::vector<std::string> cat_in_order;
std::vector<std::string> cat_sorted;
std::vector<std::string> *vec_cat[] = { &cat_in_order, &cat_sorted, 0 };

void build_lists() {
    for(auto it = ac::solo_filter.begin(); it != ac::solo_filter.end(); ++it) {
        cat_in_order.push_back(*it);
        cat_sorted.push_back(*it);
    }
    std::sort(cat_sorted.begin(), cat_sorted.end());
}