#include"filters.hpp"
#include"../new_filter.hpp"
#include "colorxor2.hpp"


void init_filters_local() {
   new_filter_list.push_back({"New_ColorXor2", new ColorXor2()});
   new_filter_list.push_back({"New_ColorXor3", new ColorXor3()});
}