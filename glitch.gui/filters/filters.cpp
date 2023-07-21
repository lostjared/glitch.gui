#include"filters.hpp"
#include"../new_filter.hpp"
#include "colorxor2.hpp"


void init_filters_local() {
   static ColorXor2 color_xor2;
   new_filter_list.push_back( {"New_ColorXor2", &color_xor2});
}