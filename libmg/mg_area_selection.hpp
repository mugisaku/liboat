#ifndef MG_AREA_SELECTION_HPP_INCLUDED
#define MG_AREA_SELECTION_HPP_INCLUDED


#include<cstdint>
#include"oat_widget.hpp"
#include"mg_image.hpp"




namespace area_selection{


struct
Rect
{
  int     top;
  int    left;
  int   right;
  int  bottom;

  Frame  to_frame() const{return Frame{left,top,right-left+1,bottom-top+1};}

};


const Rect&  get_rect();

bool  test_whether_transformed();

void  reset();

void  grab(int  x, int  y);
void  move(int  x, int  y);
void  release();

}



#endif




