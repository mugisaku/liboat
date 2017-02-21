#include"gramk_card.hpp"
#include<cstring>




void
Card::
shift_up(int  x, int  y, int  w, int  h)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < h-1;  ++yy){
    for(int  xx = 0;  xx < w  ;  ++xx){
      put(tmp.get(x+xx,y+yy+1),x+xx,y+yy);
    }}


  prepare_new_log(true);
}


void
Card::
shift_left(int  x, int  y, int  w, int  h)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < h  ;  ++yy){
    for(int  xx = 0;  xx < w-1;  ++xx){
      put(tmp.get(x+xx+1,y+yy),x+xx,y+yy);
    }}


  prepare_new_log(true);
}


void
Card::
shift_right(int  x, int  y, int  w, int  h)
{
  Card  tmp = *this;

  prepare_new_log();

   for(int  yy = 0;  yy < h;  ++yy){
   for(int  xx = 1;  xx < w;  ++xx){
     put(tmp.get(x+xx-1,y+yy),x+xx,y+yy);
   }}


  prepare_new_log(true);
}


void
Card::
shift_down(int  x, int  y, int  w, int  h)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 1;  yy < h;  ++yy){
    for(int  xx = 0;  xx < w;  ++xx){
      put(tmp.get(x+xx,y+yy-1),x+xx,y+yy);
    }}


  prepare_new_log(true);
}




void
Card::
rotate_up(int  x, int  y, int  w, int  h)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < h-1;  ++yy){
    for(int  xx = 0;  xx < w  ;  ++xx){
      put(tmp.get(x+xx,y+yy+1),x+xx,y+yy);
    }}


    for(int  xx = 0;  xx < w;  ++xx)
    {
      put(tmp.get(x+xx,y),x+xx,y+h-1);
    }


  prepare_new_log(true);
}


void
Card::
rotate_left(int  x, int  y, int  w, int  h)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < h  ;  ++yy){
    for(int  xx = 0;  xx < w-1;  ++xx){
      put(tmp.get(x+xx+1,y+yy),x+xx,y+yy);
    }}


    for(int  yy = 0;  yy < h;  ++yy)
    {
      put(tmp.get(x,y+yy),x+w-1,y+yy);
    }


  prepare_new_log(true);
}


void
Card::
rotate_right(int  x, int  y, int  w, int  h)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < h;  ++yy){
    for(int  xx = 1;  xx < w;  ++xx){
      put(tmp.get(x+xx-1,y+yy),x+xx,y+yy);
    }}


    for(int  yy = 0;  yy < h;  ++yy)
    {
      put(tmp.get(x+w-1,y+yy),x,y+yy);
    }


  prepare_new_log(true);
}


void
Card::
rotate_down(int  x, int  y, int  w, int  h)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 1;  yy < h;  ++yy){
    for(int  xx = 0;  xx < w;  ++xx){
      put(tmp.get(x+xx,y+yy-1),x+xx,y+yy);
    }}


    for(int  xx = 0;  xx < w;  ++xx)
    {
      put(tmp.get(x+xx,y+h-1),x+xx,y);
    }


  prepare_new_log(true);
}




