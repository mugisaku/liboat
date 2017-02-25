#include"gramk_card.hpp"
#include"gramk_painter.hpp"
#include<cstring>




void
Card::
revolve(const Rect&  rect)
{
  Card  tmp = *this;

  const int  w = std::min(rect.w,rect.h);

  prepare_new_log();

    for(int  yy = 0;  yy < w;  ++yy){
    for(int  xx = 0;  xx < w;  ++xx){
      put_color(tmp.get_color(rect.x+xx,rect.y+yy),rect.x+w-1-yy,rect.y+xx);
    }}


  prepare_new_log(true);
}


void
Card::
reverse_horizontally(const Rect&  rect)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < rect.h;  ++yy){
    for(int  xx = 0;  xx < rect.w;  ++xx){
      put_color(tmp.get_color(rect.x+xx,rect.y+yy),rect.x+xx,rect.y+rect.h-1-yy);
    }}


  prepare_new_log(true);
}


void
Card::
reverse_vertically(const Rect&  rect)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < rect.h;  ++yy){
    for(int  xx = 0;  xx < rect.w;  ++xx){
      put_color(tmp.get_color(rect.x+xx,rect.y+yy),rect.x+rect.w-1-xx,rect.y+yy);
    }}


  prepare_new_log(true);
}


void
Card::
mirror_vertically(const Rect&  rect)
{
  prepare_new_log();

    for(int  yy = 0;  yy < rect.h  ;  ++yy){
    for(int  xx = 0;  xx < rect.w/2;  ++xx){
      auto  v = Card::get_color(rect.x+xx,rect.y+yy);

      put_color(v,rect.x+rect.w-1-xx,rect.y+yy);
    }}


  prepare_new_log(true);
}




void
Card::
shift_up(const Rect&  rect, bool  rotate)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < rect.h-1;  ++yy){
    for(int  xx = 0;  xx < rect.w  ;  ++xx){
      put_color(tmp.get_color(rect.x+xx,rect.y+yy+1),rect.x+xx,rect.y+yy);
    }}


    if(rotate)
    {
        for(int  xx = 0;  xx < rect.w;  ++xx)
        {
          put_color(tmp.get_color(rect.x+xx,rect.y),rect.x+xx,rect.y+rect.h-1);
        }
    }


  prepare_new_log(true);
}


void
Card::
shift_left(const Rect&  rect, bool  rotate)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < rect.h  ;  ++yy){
    for(int  xx = 0;  xx < rect.w-1;  ++xx){
      put_color(tmp.get_color(rect.x+xx+1,rect.y+yy),rect.x+xx,rect.y+yy);
    }}


    if(rotate)
    {
        for(int  yy = 0;  yy < rect.h;  ++yy)
        {
          put_color(tmp.get_color(rect.x,rect.y+yy),rect.x+rect.w-1,rect.y+yy);
        }
    }


  prepare_new_log(true);
}


void
Card::
shift_right(const Rect&  rect, bool  rotate)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < rect.h;  ++yy){
    for(int  xx = 1;  xx < rect.w;  ++xx){
      put_color(tmp.get_color(rect.x+xx-1,rect.y+yy),rect.x+xx,rect.y+yy);
    }}


    if(rotate)
    {
        for(int  yy = 0;  yy < rect.h;  ++yy)
        {
          put_color(tmp.get_color(rect.x+rect.w-1,rect.y+yy),rect.x,rect.y+yy);
        }
    }


  prepare_new_log(true);
}


void
Card::
shift_down(const Rect&  rect, bool  rotate)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 1;  yy < rect.h;  ++yy){
    for(int  xx = 0;  xx < rect.w;  ++xx){
      put_color(tmp.get_color(rect.x+xx,rect.y+yy-1),rect.x+xx,rect.y+yy);
    }}


    if(rotate)
    {
        for(int  xx = 0;  xx < rect.w;  ++xx)
        {
          put_color(tmp.get_color(rect.x+xx,rect.y+rect.h-1),rect.x+xx,rect.y);
        }
    }


  prepare_new_log(true);
}





