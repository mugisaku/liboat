#ifndef GRAMK_RECT_HPP_INCLUDED
#define GRAMK_RECT_HPP_INCLUDED


#include<cstdint>
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

  void  form(const oat::Point&  p0, const oat::Point&  p1);

  void  draw(std::vector<oat::Point>&  buf) const;
  void  fill(std::vector<oat::Point>&  buf) const;

};


#endif




