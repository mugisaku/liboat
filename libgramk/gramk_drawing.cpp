#include"gramk_drawing.hpp"
#include<cstring>
#include<algorithm>




namespace drawing{


void
draw_line(void*  that, Callback  callback, int  color, int  x0, int  y0, int  x1, int  y1)
{
  constexpr int  shift_amount = 22;


  const int  x_min = std::min(x0,x1);
  const int  x_max = std::max(x0,x1);
  const int  y_min = std::min(y0,y1);
  const int  y_max = std::max(y0,y1);

  const int  x_dist = (x_max-x_min+1);
  const int  y_dist = (y_max-y_min+1);

    if(!x_dist ||
       !y_dist)
    {
      return;
    }


  int  x = (x0<<shift_amount);
  int  y = (y0<<shift_amount);

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


    if(x0 > x1){x_add_amount = -x_add_amount;}
    if(y0 > y1){y_add_amount = -y_add_amount;}


    while(dist--)
    {
      callback(that,color,(x>>shift_amount),
                          (y>>shift_amount));

      x += x_add_amount;
      y += y_add_amount;
    }
}


}




