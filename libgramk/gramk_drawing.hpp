#ifndef GRAMK_DRAWING_HPP_INCLUDED
#define GRAMK_DRAWING_HPP_INCLUDED


#include"oat.hpp"




struct
Rect
{
  int  x;
  int  y;
  int  w;
  int  h;

  constexpr Rect(int  x_=0, int  y_=0, int  w_=0, int  h_=0):
  x(x_),
  y(y_),
  w(w_),
  h(h_){}

};


namespace drawing{


using Callback = void  (*)(void*  that, int  color, int  x, int  y);

void  draw_line(void*  that, Callback  callback, int  color, const oat::Point&  p0, const oat::Point&  p1);
void  draw_rect(void*  that, Callback  callback, int  color, const Rect&  rect);
void  fill_rect(void*  that, Callback  callback, int  color, const Rect&  rect);

void  sort(oat::Point&  p0, oat::Point&  p1);

}




#endif




