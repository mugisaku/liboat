#include"gramk_painter.hpp"
#include<cstring>
#include<algorithm>




namespace{


void
move_x0(Rect&  rect, int  x, int  x_max)
{
    if(x <= rect.x)
    {
      rect.w += (rect.x-x);
    }

  else
    {
        if(x > x_max)
        {
          x = x_max;
        }


      rect.w -= x-rect.x;
    }


  rect.x = x;
}


void
move_y0(Rect&  rect, int  y, int  y_max)
{
    if(y <= rect.y)
    {
      rect.h += (rect.y-y);
    }

  else
    {
        if(y > y_max)
        {
          y = y_max;
        }


      rect.h -= y-rect.y;
    }


  rect.y = y;
}


void
move_x1(Rect&  rect, int  x)
{
    if(x < rect.x)
    {
      x = rect.x;
    }


  rect.w = x-rect.x+1;
}


void
move_y1(Rect&  rect, int  y)
{
    if(y < rect.y)
    {
      y = rect.y;
    }


  rect.h = y-rect.y+1;
}


}


void
Painter::
move_corner(int  x, int  y)
{
  auto&  rect = operating_rect;

  const int  x_max = (rect.x+rect.w-1);
  const int  y_max = (rect.y+rect.h-1);

    switch(rect_corner)
    {
  case(Corner::none):
        if(x == rect.x)
        {
               if(y == (rect.y    )){rect_corner = Corner::top_left   ;}
          else if(y == (     y_max)){rect_corner = Corner::bottom_left;}
        }

      else
        if(x == x_max)
        {
               if(y == (rect.y    )){rect_corner = Corner::top_right   ;}
          else if(y == (     y_max)){rect_corner = Corner::bottom_right;}
        }
      break;
  case(Corner::top_left):
      move_x0(rect,x,x_max);
      move_y0(rect,y,y_max);
      break;
  case(Corner::top_right):
      move_x1(rect,x      );
      move_y0(rect,y,y_max);
      break;
  case(Corner::bottom_left):
      move_x0(rect,x,x_max);
      move_y1(rect,y      );
      break;
  case(Corner::bottom_right):
      move_x1(rect,x);
      move_y1(rect,y);
      break;
    }
}





