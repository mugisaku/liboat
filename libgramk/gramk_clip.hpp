#ifndef GRAMK_CLIP_HPP_INCLUDED
#define GRAMK_CLIP_HPP_INCLUDED


#include"gramk_card.hpp"




class
Clip
{
  uint8_t  pixels[Card::height][Card::width];

  int   width;
  int  height;

public:
  void  change_size(int  w, int  h);

  int  get_width()  const;
  int  get_height() const;

  uint8_t  get(                int  x, int  y) const;
  void     put(uint8_t  pixel, int  x, int  y)      ;

  void  clear();

};


#endif




