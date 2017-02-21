#ifndef GRAMK_CARD_HPP_INCLUDED
#define GRAMK_CARD_HPP_INCLUDED


#include<cstdint>
#include"oat.hpp"




class
Card
{
public:
  static constexpr int  fixed_width  = 24;
  static constexpr int  fixed_height = 48;

protected:

  uint8_t  color_table[fixed_height][fixed_width];

public:
  Card();

  uint8_t  get(                int  x, int  y) const;
  void     put(uint8_t  color, int  x, int  y)      ;

  void  clear();

  void  draw(oat::Widget&  dst, int  x, int  y, int  pixel_size=1) const;

};


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


#endif




