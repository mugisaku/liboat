#include"gramk_painter.hpp"
#include"gramk_drawing.hpp"
#include<cstring>



Painter::
Painter(Callback  cb):
target(nullptr),
callback(cb),
current_color(8|15),
drawing_rect(0,0,SuperCard::width,SuperCard::height)
{
  change_content_width( SuperCard::width *pixel_size);
  change_content_height(SuperCard::height*pixel_size);

  style.background_color = oat::const_color::blue;

  change_mode(PaintingMode::draw_point);
}




void
Painter::
change_target(SuperCard&  card)
{
  target = &card;

  need_to_redraw();
}


void  Painter::change_current_color(uint8_t  color){current_color = color;}


void
Painter::
change_mode(PaintingMode  mode_)
{
  mode = mode_;

   selected_flag = false;
  composing_flag = false;

  need_to_redraw();
}


SuperCard*  Painter::get_target() const{return target;}


uint8_t  Painter::get_current_color() const{return current_color;}


const Rect&  Painter::get_drawing_rect() const{return drawing_rect;}


void
Painter::
copy()
{
  Rect  rect = selected_flag? selected_rect:Rect(0,0,SuperCard::width,SuperCard::height);

  target->get(copy_clip,rect);
}


void
Painter::
process_mouse(const oat::Mouse&  mouse)
{
    if(!target)
    {
      return;
    }


  auto  pt = get_mouse_point(mouse);

  int  x = pt.x/pixel_size;
  int  y = pt.y/pixel_size;

    switch(mode)
    {
  case(PaintingMode::draw_point):
        if(mouse.left.test_pressing())
        {
          target->put(current_color|8,x,y);
        }

      else
        if(mouse.right.test_pressing())
        {
          target->put(0,x,y);
        }
      break;
  case(PaintingMode::draw_line):
           if(mouse.left.test_pressing()){process_draw_line(true,current_color|8,x,y);}
      else if(mouse.right.test_pressing()){process_draw_line(true,0,x,y);}
      else if(mouse.left.test_unpressed()){process_draw_line(false,current_color|8,x,y);}
      else if(mouse.right.test_unpressed()){process_draw_line(false,0,x,y);}
      break;
  case(PaintingMode::draw_rect):
           if(mouse.left.test_pressing()){process_draw_line(true,current_color|8,x,y);}
      else if(mouse.right.test_pressing()){process_draw_line(true,0,x,y);}
      else if(mouse.left.test_unpressed()){process_draw_line(false,current_color|8,x,y);}
      else if(mouse.right.test_unpressed()){process_draw_line(false,0,x,y);}
      break;
  case(PaintingMode::fill_rect):
           if(mouse.left.test_pressing()){process_draw_line(true,current_color|8,x,y);}
      else if(mouse.right.test_pressing()){process_draw_line(true,0,x,y);}
      else if(mouse.left.test_unpressed()){process_draw_line(false,current_color|8,x,y);}
      else if(mouse.right.test_unpressed()){process_draw_line(false,0,x,y);}
      break;
  case(PaintingMode::fill_area):
        if(mouse.left.test_pressing())
        {
          target->fill_area(current_color|8,x,y);
        }

      else
        if(mouse.right.test_pressing())
        {
          target->fill_area(0,x,y);
        }
      break;
  case(PaintingMode::transform_area_frame):
        if(mouse.left.test_pressed())
        {
//          area_selection::grab(x,y);
        }

      else
        if(mouse.left.test_pressing())
        {
//          area_selection::move(x,y);
        }
      break;
  case(PaintingMode::paste):
        if(mouse.left.test_pressing())
        {
          composing_flag = true;

          temporary_clip.clear();

          temporary_clip.put(copy_clip,x,y);
        }

      else
        if(mouse.left.test_unpressed())
        {
          composing_flag = false;

          target->put(copy_clip,x,y,true);
        }
      break;
  case(PaintingMode::layer):
        if(mouse.left.test_pressing())
        {
          composing_flag = true;

          temporary_clip.clear();

          temporary_clip.put(copy_clip,x,y);
        }

      else
        if(mouse.left.test_unpressed())
        {
          composing_flag = false;

          target->put(copy_clip,x,y,false);
        }
      break;
    }


  need_to_redraw();

  callback(nullptr);
}




void
Painter::
draw_selection_frame()
{
/*
  auto&  pt = content.point;

  auto&  rect = area_selection::get_rect();

  draw_rect(oat::const_color::yellow,pt.x+(pixel_size*rect.left),
                                     pt.y+(pixel_size*rect.top),
                                     (pixel_size*((rect.right-rect.left)+1)),
                                     (pixel_size*((rect.bottom-rect.top)+1)));

  draw_rect(oat::const_color::yellow,pt.x+(pixel_size*rect.left),
                                     pt.y+(pixel_size*rect.top),
                                     pixel_size,
                                     pixel_size);

  draw_rect(oat::const_color::yellow,pt.x+(pixel_size*rect.right),
                                     pt.y+(pixel_size*rect.top),
                                     pixel_size,
                                     pixel_size);

  draw_rect(oat::const_color::yellow,pt.x+(pixel_size*rect.left),
                                     pt.y+(pixel_size*rect.bottom),
                                     pixel_size,
                                     pixel_size);

  draw_rect(oat::const_color::yellow,pt.x+(pixel_size*rect.right),
                                     pt.y+(pixel_size*rect.bottom),
                                     pixel_size,
                                     pixel_size);
*/
}


void
Painter::
render()
{
  fill();

    if(!target)
    {
      return;
    }


  auto  pt = content.point;

  constexpr oat::Color  l1(0x7F,0x7F,0x0);
  constexpr oat::Color  l2(0xFF,0xFF,0x00);

  constexpr int  w = SuperCard::width ;
  constexpr int  h = SuperCard::height;

  target->draw(*this,pt.x,pt.y,pixel_size);

    if(composing_flag)
    {
      temporary_clip.draw(*this,pt.x,pt.y,pixel_size);
    }


    for(int  y = 0;  y < h;  ++y)
    {
        for(int  x = 0;  x < w;  ++x)
        {
          draw_vline(l1,pt.x+pixel_size*x,
                        pt.y,
                        pixel_size*h);
        }


      draw_hline(l1,pt.x,
                    pt.y+pixel_size*y,
                    pixel_size*w);
    }


  draw_hline(l2,pt.x,
                pt.y+pixel_size*(h/2)+1,
                pixel_size*w);

  draw_vline(l2,pt.x+pixel_size*(w/2)+1,
                pt.y,
                pixel_size*h);



/*
    if(grid_extent)
    {
      draw_rect(l2,pt.x+pixel_size*4+1,
                   pt.y+pixel_size*4+1,
                   pixel_size*(w-8),
                   pixel_size*(h-8));
    }


    if((PaintingMode::get_index() == tool_selection::transform_area_frame) ||
        area_selection::test_whether_transformed())
    {
      draw_selection_frame();
    }
*/
}



