#include"gramk_painter.hpp"
#include"gramk_drawing.hpp"
#include<cstring>



namespace{


void
draw_preview_line(void*  that, int  color, int  x, int  y)
{
  auto&  c = *static_cast<Clip*>(that);

  c.put(color,x,y);
}


void
draw_line(void*  that, int  color, int  x, int  y)
{
  auto&  c = *static_cast<Card*>(that);

  c.put(color,x,y);
}


}




void
Painter::
process_draw_line(bool  button, int  color, int  x, int  y)
{
    if(button)
    {
        if(point0.x < 0)
        {
          point0.reset(x,y);
        }

      else
        {
          point1.reset(x,y);

          target->get(preview_clip,0,0,0,0);

          preview_flag = true;

          drawing::draw_line(&preview_clip,draw_preview_line,color,point0.x,point0.y,point1.x,point1.y);
        }
    }

  else
    {
      target->prepare_new_log();

      drawing::draw_line(target,::draw_line,color,point0.x,point0.y,point1.x,point1.y);

      target->prepare_new_log(true);

      point0.x = -1;

      preview_flag = false;
    }
}




