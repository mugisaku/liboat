#ifndef GRAMK_CLIP_HPP_INCLUDED
#define GRAMK_CLIP_HPP_INCLUDED


#include"gramk_card.hpp"




class
Clip: public Card
{
  int   width;
  int  height;

public:
  void  change_size(int  w, int  h);

  int  get_width()  const;
  int  get_height() const;

  void  put(const Clip&  src, int  x, int  y);

};


#endif




