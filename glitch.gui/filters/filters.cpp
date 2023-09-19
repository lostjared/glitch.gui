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
    new_filter_list.push_back({"New_Glitch_RandRect_X2_Wrap", new Glitch_RandRect_X2_Wrap()});
    new_filter_list.push_back({"New_Glitch_RandRect_X3", new Glitch_RandRect_X3()});
    new_filter_list.push_back({"New_Glitch_RandRect_X4", new Glitch_RandRect_X4()});
    new_filter_list.push_back({"New_Glitch_Pixel_X1", new Glitch_Pixel_X1()});
    new_filter_list.push_back({"New_SimpleTrails", new SimpleTrails()});
    new_filter_list.push_back({"New_Glitch_Mirror_Shift", new Glitch_Mirror_Shift()});
    new_filter_list.push_back({"New_Glitch_Mirror_Shift_Xor", new Glitch_Mirror_Shift_Xor()});
    new_filter_list.push_back({"New_Glitch_Mirror_Slice", new Glitch_Mirror_Slice()});
    new_filter_list.push_back({"New_Glitch_Mirror_Slice_Rand", new Glitch_Mirror_Slice_Rand()});
    new_filter_list.push_back({"New_Glitch_Mirror_Slice_Inc", new Glitch_Mirror_Slice_Inc()});
    new_filter_list.push_back({"New_Glitch_Mirror_Slice_Inc_X2", new Glitch_Mirror_Slice_Inc_X2()});
    new_filter_list.push_back({"New_Glitch_Mirror_Slice_X2", new Glitch_Mirror_Slice_Inc_X2()});
    new_filter_list.push_back({"New_Glitch_Mirror_Bars", new Glitch_Mirror_Bars()});
    new_filter_list.push_back({"New_Glitch_Mirror_Bars_X2", new Glitch_Mirror_Bars_X2()});
    new_filter_list.push_back({"New_Glitch_Mirror_Bars_Col", new Glitch_Mirror_Bars_Col()});
    new_filter_list.push_back({"New_Glitch_Mirror_Bars_Col_Orig", new Glitch_Mirror_Bars_Col_Orig()});
    new_filter_list.push_back({"New_Glitch_Mirror_Bars_Col_OrigY", new Glitch_Mirror_Bars_Col_OrigY()});
    new_filter_list.push_back({"New_Glitch_Mirror_Bars_Col_OrigYH", new Glitch_Mirror_Bars_Col_OrigYH()});
    new_filter_list.push_back({"New_Glitch_Mirror_Bars_Col_OrigYH_Pixels", new Glitch_Mirror_Bars_Col_OrigYH_Pixels()});
    new_filter_list.push_back({"New_Glitch_Mirror_Bars_Col_OrigY_Grad", new Glitch_Mirror_Bars_Col_OrigY_Grad()});
    new_filter_list.push_back({"New_Glitch_Mirror_Bars_Col_OrigY_Grad_Overflow", new Glitch_Mirror_Bars_Col_OrigY_Grad_Overflow()});
    new_filter_list.push_back({"New_Glitch_Mirror_Bars_Horiz", new Glitch_Mirror_Bars_Horiz()});
    new_filter_list.push_back({"New_Glitch_Mirror_Bars_Horiz_X1", new Glitch_Mirror_Bars_Horiz_X1()});
    new_filter_list.push_back({"New_Glitch_Mirror_Bars_Horiz_X1_Grad", new Glitch_Mirror_Bars_Horiz_X1_Grad()});
    new_filter_list.push_back({"New_Glitch_Mirror_Bars_Horiz_X1_Grad_Xor", new Glitch_Mirror_Bars_Horiz_X1_Grad_Xor()});
    new_filter_list.push_back({"New_Glitch_Line_Horiz", new Glitch_Line_Horiz()});
    new_filter_list.push_back({"New_Glitch_Line_Horiz_Grad", new Glitch_Line_Horiz_Grad()});
    new_filter_list.push_back({"New_Glitch_Rect_Grad", new Glitch_Rect_Grad()});
    new_filter_list.push_back({"New_Glitch_Rect_Size", new Glitch_Rect_Size()});
    new_filter_list.push_back({"New_Glitch_Rect_SizeY", new Glitch_Rect_SizeY()});
    new_filter_list.push_back({"New_Glitch_Rect_SizeX", new Glitch_Rect_SizeX()}); 
    new_filter_list.push_back({"New_Glitch_Rect_Size_Odd", new Glitch_Rect_Size_Odd()}); 
    new_filter_list.push_back({"New_Glitch_Rect_Size_Overflow", new Glitch_Rect_Size_Overflow()}); 
    new_filter_list.push_back({"New_Glitch_Rect_Size_Fast", new Glitch_Rect_Size_Fast()});  
    new_filter_list.push_back({"New_Glitch_Rect_Size_Slow", new Glitch_Rect_Size_Slow()});  
    new_filter_list.push_back({"New_Glitch_Rect_Size_Row", new Glitch_Rect_Size_Row()});
    new_filter_list.push_back({"New_Glitch_Rect_Size_Row_Rand", new Glitch_Rect_Size_Row_Rand()});

}