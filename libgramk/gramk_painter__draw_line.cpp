#include"gramk_painter.hpp"
#include"gramk_drawing.hpp"
#include<cstring>



namespace{


void
draw_preview_line(void*  that, int  color, int  x, int  y)
{
  auto&  c = *static_cast<Clip*>(that);

  c.Card::put(color,x,y);
}


void
draw_line(void*  that, int  color, int  x, int  y)
{
  auto&  c = *static_cast<SuperCard*>(that);

  c.put(color,x,y);
}


}




void
Painter::
process_draw_line(bool  button, int  color, int  x, int  y)
{
    if(button)
    {
        if(!selected_flag)
        {
          selected_flag = true;

          point0.reset(x,y);

          temporary_clip.change_size(SuperCard::width,SuperCard::height);
        }

      else
        {
          point1.reset(x,y);

          composing_flag = true;

          temporary_clip.clear();

          drawing::draw_line(&temporary_clip,draw_preview_line,color,point0.x,point0.y,point1.x,point1.y);
        }
    }

  else
    {
      target->prepare_new_log();

      drawing::draw_line(target,::draw_line,color,point0.x,point0.y,point1.x,point1.y);

      target->prepare_new_log(true);

       selected_flag = false;
      composing_flag = false;
    }
}




