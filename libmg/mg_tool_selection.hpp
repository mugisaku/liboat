#ifndef MG_TOOL_SELECTION_HPP_INCLUDED
#define MG_TOOL_SELECTION_HPP_INCLUDED


#include<cstdint>
#include"oat.hpp"




namespace tool_selection{


constexpr int  draw_point = 0;
constexpr int  fill_area  = 1;
constexpr int  transform_area_frame = 2;
constexpr int  paste = 3;
constexpr int  layer = 4;


int  get_index();

oat::Widget*  create_widget();


}



#endif




