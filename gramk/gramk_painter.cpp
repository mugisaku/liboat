#include"gramk_painter.hpp"
#include<cstring>
#include<algorithm>




Painter::
Painter(Callback  cb):
target(nullptr),
callback(cb),
current_color(0),
operating_rect(0,0,Card::width,Card::height),
selecting_state(0),
rect_corner(Corner::none)
{
  change_content_width( Card::width *pixel_size);
  change_content_height(Card::height*pixel_size);

  style.background_color = oat::const_color::blue;

  change_mode(PaintingMode::draw_point);
}




void
Painter::
change_target(Card&  card)
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

    if(mode == PaintingMode::transform_area_frame)
    {
        if(selecting_state == 1)
        {
          selecting_state = 2;
        }
    }

  else
    {
        if(selecting_state == 2)
        {
          selecting_state = 1;
        }
    }


   pointing_flag = false;
  composing_flag = false;

  single_pointing_flag = ((mode == PaintingMode::draw_point) ||
                          (mode == PaintingMode::fill_area)  ||
                          (mode == PaintingMode::paste)      ||
                          (mode == PaintingMode::layer));


  need_to_redraw();
}


Card*  Painter::get_target() const{return target;}


uint8_t  Painter::get_current_color() const{return current_color;}


const Rect&
Painter::
get_operating_rect() const
{
  return operating_rect;
}


const Rect&
Painter::
get_selecting_rect() const
{
  return selecting_state? selecting_rect:Card::whole_rect;
}




void
Painter::
make_pointing(int  x, int  y)
{
    if(!pointing_flag)
    {
      point0.reset(x,y);
      point1.reset(x,y);

      pointing_flag = true;
    }

  else
    {
      point1.reset(x,y);

      Card::transfer(*target,Card::whole_rect,temporary_card,0,0,true);

        switch(mode)
        {
      case(PaintingMode::draw_line):
          composing_flag = true;

          temporary_card.draw_line(current_color|8,point0,point1);
          break;
      case(PaintingMode::draw_rect):
          composing_flag = true;

          operating_rect.form(point0,point1);

          temporary_card.draw_rect(current_color|8,operating_rect);
          break;
      case(PaintingMode::fill_rect):
          composing_flag = true;

          operating_rect.form(point0,point1);

          temporary_card.fill_rect(current_color|8,operating_rect);
          break;
      case(PaintingMode::transform_area_frame):
          selecting_rect.form(point0,point1);

          selecting_state = 1;
          break;
        }
    }
}




void
Painter::
copy()
{
  copy_card.clear();

  auto&  rect = selecting_rect;

  Card::transfer(*target,rect,copy_card,0,0,true);

  copy_rect.w = rect.w;
  copy_rect.h = rect.h;
}


void
Painter::
paste(int  x, int  y, bool  overwrite, bool  rehearsal)
{
  composing_flag = true;

  paste_point.reset(x,y);

    if(rehearsal)
    {
      Card::transfer(  *target,Card::whole_rect,temporary_card,0,0,true);
      Card::transfer(copy_card,       copy_rect,temporary_card,x,y,overwrite);
    }

  else
    {
      target->prepare_new_log();

      Card::transfer(copy_card,copy_rect,*target,x,y,overwrite);

      target->prepare_new_log(true);
    }
}


void
Painter::
fill_area(int  color, int  x, int  y)
{
  target->prepare_new_log();

  target->fill_area(color,x,y);

  target->prepare_new_log(true);
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

    if(single_pointing_flag)
    {
        switch(mode)
        {
      case(PaintingMode::draw_point):
               if(mouse.left.test_pressing() ){target->put_color(current_color|8,x,y);}
          else if(mouse.right.test_pressing()){target->put_color(              0,x,y);}
          break;
      case(PaintingMode::fill_area):
               if(mouse.left.test_pressing() ){fill_area(current_color|8,x,y);}
          else if(mouse.right.test_pressing()){fill_area(              0,x,y);}
          break;
      case(PaintingMode::paste):
            if(mouse.left.test_unpressed()){paste(x,y,true,false);}
          else                             {paste(x,y,true,true );}
          break;
      case(PaintingMode::layer):
            if(mouse.left.test_unpressed()){paste(x,y,false,false);}
          else                             {paste(x,y,false,true );}
          break;
        }
    }

  else
    if(mouse.right.test_pressing())
    {
      pointing_flag = false;

        if(mode == PaintingMode::transform_area_frame)
        {
          selecting_state = 0;
        }
    }

  else
    if(mouse.left.test_pressing())
    {
        if(selecting_state == 2){move_corner(  x,y);}
      else                      {make_pointing(x,y);}
    }

  else
    if(mouse.left.test_unpressed())
    {
        switch(mode)
        {
      case(PaintingMode::draw_line):
          target->prepare_new_log();

          target->draw_line(current_color|8,point0,point1);

          target->prepare_new_log(true);
          break;
      case(PaintingMode::draw_rect):
          target->prepare_new_log();

          target->draw_rect(current_color|8,operating_rect);

          target->prepare_new_log(true);
          break;
      case(PaintingMode::fill_rect):
          target->prepare_new_log();

          target->fill_rect(current_color|8,operating_rect);

          target->prepare_new_log(true);
          break;
      case(PaintingMode::transform_area_frame):
          selecting_state = 2;

          rect_corner = Corner::none;
          break;
        }


       pointing_flag = false;
      composing_flag = false;
    }


  need_to_redraw();

  callback(nullptr);
}




void
Painter::
draw_selecting_rect()
{
  auto&  pt = content.point;

  const auto&  rect = selecting_rect;

  draw_rect(oat::const_color::yellow,pt.x+(pixel_size*rect.x),
                                     pt.y+(pixel_size*rect.y),
                                          (pixel_size*rect.w),
                                          (pixel_size*rect.h));

    if(selecting_state == 2)
    {
      draw_rect(oat::const_color::yellow,pt.x+(pixel_size*rect.x),
                                         pt.y+(pixel_size*rect.y),
                                         pixel_size,
                                         pixel_size);

      draw_rect(oat::const_color::yellow,pt.x+(pixel_size*(rect.x+rect.w-1)),
                                         pt.y+(pixel_size*(rect.y         )),
                                         pixel_size,
                                         pixel_size);

      draw_rect(oat::const_color::yellow,pt.x+(pixel_size*(rect.x         )),
                                         pt.y+(pixel_size*(rect.y+rect.h-1)),
                                         pixel_size,
                                         pixel_size);

      draw_rect(oat::const_color::yellow,pt.x+(pixel_size*(rect.x+rect.w-1)),
                                         pt.y+(pixel_size*(rect.y+rect.h-1)),
                                         pixel_size,
                                         pixel_size);
    }
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

  constexpr int  w = Card::width ;
  constexpr int  h = Card::height;


    if(composing_flag)
    {
      temporary_card.render(Card::width,Card::height,*this,pt.x,pt.y,pixel_size);
    }

  else
    {
      target->render(Card::width,Card::height,*this,pt.x,pt.y,pixel_size);
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

    if(selecting_state)
    {
      draw_selecting_rect();
    }
}




