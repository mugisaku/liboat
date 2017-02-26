#include"gramk_card.hpp"
#include<cstring>
#include<algorithm>




void
Card::
draw_line(int  color, const oat::Point&  p0, const oat::Point&  p1)
{
/*
  constexpr int  shift_amount = 24;

  const int  x_dist = (p0.x < p1.x)? (p1.x-p0.x)+1:(p0.x-p1.x)+1;
  const int  y_dist = (p0.y < p1.y)? (p1.y-p0.y)+1:(p0.y-p1.y)+1;

    if(!x_dist ||
       !y_dist)
    {
      return;
    }


  int  dist;

  int  x_add_amount;
  int  y_add_amount;

    if(x_dist < y_dist)
    {
      dist = y_dist;

      x_add_amount = (x_dist<<shift_amount)/y_dist;
      y_add_amount = (     1<<shift_amount)       ;
    }

  else
    if(x_dist > y_dist)
    {
      dist = x_dist;

      x_add_amount = (     1<<shift_amount)       ;
      y_add_amount = (y_dist<<shift_amount)/x_dist;
    }

  else
    {
      dist = x_dist;

      x_add_amount = 1<<shift_amount;
      y_add_amount = 1<<shift_amount;
    }


    if(p0.x > p1.x){x_add_amount = -x_add_amount;}
    if(p0.y > p1.y){y_add_amount = -y_add_amount;}


  int  x_val = (p0.x<<shift_amount);
  int  y_val = (p0.y<<shift_amount);

    while(dist--)
    {
      const int  x = (x_val>>shift_amount);
      const int  y = (y_val>>shift_amount);

      put_color(color,x,y);

        if((x == p1.x) &&
           (y == p1.y))
        {
          break;
        }


      x_val += x_add_amount;
      y_val += y_add_amount;
    }
*/
int  x0 = p0.x;
int  y0 = p0.y;
int  x1 = p1.x;
int  y1 = p1.y;

   int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
   int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1; 
   int err = dx+dy, e2; /* error value e_xy */
 
   for(;;){  /* loop */
      put_color(color,x0,y0);
      if (x0==x1 && y0==y1) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
   }}


void
Card::
draw_rect(int  color, const Rect&  rect)
{
    for(int  xx = 0;  xx < rect.w;  ++xx)
    {
      put_color(color,rect.x+xx,rect.y         );
      put_color(color,rect.x+xx,rect.y+rect.h-1);
    }


    for(int  yy = 1;  yy < rect.h-1;  ++yy)
    {
      put_color(color,rect.x         ,rect.y+yy);
      put_color(color,rect.x+rect.w-1,rect.y+yy);
    }
}


void
Card::
fill_rect(int  color, const Rect&  rect)
{
    for(int  yy = 0;  yy < rect.h;  ++yy){
    for(int  xx = 0;  xx < rect.w;  ++xx){
      put_color(color,rect.x+xx,rect.y+yy);
    }}
}




