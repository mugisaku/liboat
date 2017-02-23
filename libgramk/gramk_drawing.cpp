#include"gramk_drawing.hpp"
#include<cstring>
#include<algorithm>




namespace drawing{


void
draw_line(void*  that, Callback  callback, int  color, const oat::Point&  p0, const oat::Point&  p1)
{
  constexpr int  shift_amount = 22;

  const int  x_min = std::min(p0.x,p1.x);
  const int  x_max = std::max(p0.x,p1.x);
  const int  y_min = std::min(p0.y,p1.y);
  const int  y_max = std::max(p0.y,p1.y);

  const int  x_dist = (x_max-x_min+1);
  const int  y_dist = (y_max-y_min+1);

    if(!x_dist ||
       !y_dist)
    {
      return;
    }


  int  x = (p0.x<<shift_amount);
  int  y = (p0.y<<shift_amount);

  int  dist;

  int  x_add_amount;
  int  y_add_amount;

    if(x_dist < y_dist)
    {
      dist = y_dist;

      x_add_amount = (x_dist<<shift_amount)/y_dist;
      y_add_amount = 1<<shift_amount;
    }

  else
    if(x_dist > y_dist)
    {
      dist = x_dist;

      x_add_amount = 1<<shift_amount;
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


    while(dist--)
    {
      callback(that,color,(x>>shift_amount),
                          (y>>shift_amount));

      x += x_add_amount;
      y += y_add_amount;
    }
}


void
draw_rect(void*  that, Callback  callback, int  color, const Rect&  rect)
{
    for(int  xx = 0;  xx < rect.w;  ++xx)
    {
      callback(that,color,rect.x+xx,rect.y         );
      callback(that,color,rect.x+xx,rect.y+rect.h-1);
    }


    for(int  yy = 1;  yy < rect.h-1;  ++yy)
    {
      callback(that,color,rect.x         ,rect.y+yy);
      callback(that,color,rect.x+rect.w-1,rect.y+yy);
    }
}


void
fill_rect(void*  that, Callback  callback, int  color, const Rect&  rect)
{
    for(int  yy = 0;  yy < rect.h;  ++yy){
    for(int  xx = 0;  xx < rect.w;  ++xx){
      callback(that,color,rect.x+xx,rect.y+yy);
    }}
}


void
sort(oat::Point&  p0, oat::Point&  p1)
{
    if(p0.x > p1.x)
    {
      std::swap(p0.x,p1.x);
    }


    if(p0.y > p1.y)
    {
      std::swap(p0.y,p1.y);
    }
}


}




