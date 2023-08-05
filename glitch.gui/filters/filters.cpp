#include"filters.hpp"
#include"../new_filter.hpp"
#include "colorxor2.hpp"
#include "trails.hpp"
#include "glitch.hpp"

void init_filters_local() {
    new_filter_list.push_back({"New_ColorXor2", new ColorXor2()});
    new_filter_list.push_back({"New_ColorXor3", new ColorXor3()});
    new_filter_list.push_back({"New_ColorXor4", new ColorXor4()});
    new_filter_list.push_back({"New_ColorXor5", new ColorXor5()});
    new_filter_list.push_back({"New_ColorXor6", new ColorXor6()});
    
    new_filter_list.push_back({"New_Glitch_Line_Down", new Glitch_Line_Down()});
    new_filter_list.push_back({"New_Glitch_Line_Down_X2", new Glitch_Line_Down_X2()});
    new_filter_list.push_back({"New_Glitch_Line_Down_X3", new Glitch_Line_Down_X3()});
    new_filter_list.push_back({"New_Glitch_Line_Down_X4", new Glitch_Line_Down_X4()});
    new_filter_list.push_back({"New_Glitch_Line_Down_X5", new Glitch_Line_Down_X5()});
    new_filter_list.push_back({"New_Glitch_RandRect", new Glitch_RandRect()});
    new_filter_list.push_back({"New_Glitch_RandRect_X2", new Glitch_RandRect_X2()});
    new_filter_list.push_back({"New_SimpleTrails", new SimpleTrails()});
}
