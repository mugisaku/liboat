#include"gramk_supercard.hpp"
#include<cstring>




void
SuperCard::
shift_up(const Rect&  rect)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < rect.h-1;  ++yy){
    for(int  xx = 0;  xx < rect.w  ;  ++xx){
      put(tmp.get(rect.x+xx,rect.y+yy+1),rect.x+xx,rect.y+yy);
    }}


  prepare_new_log(true);
}


void
SuperCard::
shift_left(const Rect&  rect)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < rect.h  ;  ++yy){
    for(int  xx = 0;  xx < rect.w-1;  ++xx){
      put(tmp.get(rect.x+xx+1,rect.y+yy),rect.x+xx,rect.y+yy);
    }}


  prepare_new_log(true);
}


void
SuperCard::
shift_right(const Rect&  rect)
{
  Card  tmp = *this;

  prepare_new_log();

   for(int  yy = 0;  yy < rect.h;  ++yy){
   for(int  xx = 1;  xx < rect.w;  ++xx){
     put(tmp.get(rect.x+xx-1,rect.y+yy),rect.x+xx,rect.y+yy);
   }}


  prepare_new_log(true);
}


void
SuperCard::
shift_down(const Rect&  rect)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 1;  yy < rect.h;  ++yy){
    for(int  xx = 0;  xx < rect.w;  ++xx){
      put(tmp.get(rect.x+xx,rect.y+yy-1),rect.x+xx,rect.y+yy);
    }}


  prepare_new_log(true);
}




void
SuperCard::
rotate_up(const Rect&  rect)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < rect.h-1;  ++yy){
    for(int  xx = 0;  xx < rect.w  ;  ++xx){
      put(tmp.get(rect.x+xx,rect.y+yy+1),rect.x+xx,rect.y+yy);
    }}


    for(int  xx = 0;  xx < rect.w;  ++xx)
    {
      put(tmp.get(rect.x+xx,rect.y),rect.x+xx,rect.y+rect.h-1);
    }


  prepare_new_log(true);
}


void
SuperCard::
rotate_left(const Rect&  rect)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < rect.h  ;  ++yy){
    for(int  xx = 0;  xx < rect.w-1;  ++xx){
      put(tmp.get(rect.x+xx+1,rect.y+yy),rect.x+xx,rect.y+yy);
    }}


    for(int  yy = 0;  yy < rect.h;  ++yy)
    {
      put(tmp.get(rect.x,rect.y+yy),rect.x+rect.w-1,rect.y+yy);
    }


  prepare_new_log(true);
}


void
SuperCard::
rotate_right(const Rect&  rect)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < rect.h;  ++yy){
    for(int  xx = 1;  xx < rect.w;  ++xx){
      put(tmp.get(rect.x+xx-1,rect.y+yy),rect.x+xx,rect.y+yy);
    }}


    for(int  yy = 0;  yy < rect.h;  ++yy)
    {
      put(tmp.get(rect.x+rect.w-1,rect.y+yy),rect.x,rect.y+yy);
    }


  prepare_new_log(true);
}


void
SuperCard::
rotate_down(const Rect&  rect)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 1;  yy < rect.h;  ++yy){
    for(int  xx = 0;  xx < rect.w;  ++xx){
      put(tmp.get(rect.x+xx,rect.y+yy-1),rect.x+xx,rect.y+yy);
    }}


    for(int  xx = 0;  xx < rect.w;  ++xx)
    {
      put(tmp.get(rect.x+xx,rect.y+rect.h-1),rect.x+xx,rect.y);
    }


  prepare_new_log(true);
}




