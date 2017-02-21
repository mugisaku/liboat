#ifndef GRAMK_PACKET_HPP_INCLUDED
#define GRAMK_PACKET_HPP_INCLUDED


#include<cstdint>
#include<vector>


struct
Dot
{
  uint8_t  color;
  uint8_t      x;
  uint8_t      y;

  constexpr Dot(uint8_t  color_=0, uint8_t  x_=0, uint8_t  y_=0):
  color(color_), x(x_), y(y_)
  {}

};


struct
Packet
{
  std::vector<Dot>  stack;

  int  solid_flag;

  Packet(std::vector<Dot>&&  stk, int  sol):
  stack(std::move(stk)), solid_flag(sol){}

};


#endif




