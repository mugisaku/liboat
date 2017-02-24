#include"gramk_painter.hpp"
#include"gramk_drawing.hpp"
#include<cstring>
#include<algorithm>




Painter::
Painter(Callback  cb):
target(nullptr),
callback(cb),
current_color(0),
operating_rect(0,0,SuperCard::width,SuperCard::height),
selecting_state(0),
rect_corner(Corner::none)
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

       if(selecting_state == 1){selecting_state = 2;}
  else if(selecting_state == 2){selecting_state = 1;}


  composing_flag  = false;

  point0.x = -1;
  point1.x = -1;

  single_pointing_flag = ((mode == PaintingMode::draw_point) ||
                          (mode == PaintingMode::fill_area)  ||
                          (mode == PaintingMode::paste)      ||
                          (mode == PaintingMode::layer));

  need_to_redraw();
}


SuperCard*  Painter::get_target() const{return target;}


uint8_t  Painter::get_current_color() const{return current_color;}


const Rect&  Painter::get_operating_rect() const{return operating_rect;}


void
Painter::
copy()
{
  Rect  rect = (point0.x >= 0)? operating_rect:Rect(0,0,SuperCard::width,SuperCard::height);

  target->get(copy_clip,rect);
}




namespace{
void
clip_cb(void*  that, int  color, int  x, int  y)
{
  auto&  c = *static_cast<Clip*>(that);

  c.Card::put(color,x,y);
}


void
scard_cb(void*  that, int  color, int  x, int  y)
{
  auto&  c = *static_cast<SuperCard*>(that);

  c.put(color,x,y);
}
}




void
Painter::
make_pointing(int  x, int  y)
{
    if(point0.x < 0)
    {
      point0.reset(x,y);
      point1.reset(x,y);

      temporary_clip.change_size(SuperCard::width,SuperCard::height);

      composing_flag = true;
    }

  else
    {
      point1.reset(x,y);

      temporary_clip.clear();

        switch(mode)
        {
      case(PaintingMode::draw_line):
          drawing::draw_line(&temporary_clip,clip_cb,current_color,point0,point1);
          break;
      case(PaintingMode::draw_rect):
          form_rect();

          drawing::draw_rect(&temporary_clip,clip_cb,current_color,operating_rect);
          break;
      case(PaintingMode::fill_rect):
          form_rect();

          drawing::fill_rect(&temporary_clip,clip_cb,current_color,operating_rect);
          break;
      case(PaintingMode::transform_area_frame):
          form_rect();

          selecting_state = 1;
          break;
        }
    }
}


void
Painter::
form_rect()
{
  const int  x_min = std::min(point0.x,point1.x);
  const int  x_max = std::max(point0.x,point1.x);
  const int  y_min = std::min(point0.y,point1.y);
  const int  y_max = std::max(point0.y,point1.y);

  operating_rect.x =       x_min;
  operating_rect.y =       y_min;
  operating_rect.w = x_max-x_min+1;
  operating_rect.h = y_max-y_min+1;
}




void
Painter::
paste(int  x, int  y, HowToPaste  how)
{
    if(how == HowToPaste::rehearsal)
    {
      composing_flag = true;

      temporary_clip.clear();

      temporary_clip.put(copy_clip,x,y);
    }

  else
    {
      composing_flag = false;

      target->put(copy_clip,x,y,(how == HowToPaste::production_with_overwrite));
    }
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
               if(mouse.left.test_pressing() ){target->put(current_color|8,x,y);}
          else if(mouse.right.test_pressing()){target->put(              0,x,y);}
          break;
      case(PaintingMode::fill_area):
               if(mouse.left.test_pressing() ){target->fill_area(current_color|8,x,y);}
          else if(mouse.right.test_pressing()){target->fill_area(              0,x,y);}
          break;
      case(PaintingMode::paste):
               if(mouse.left.test_pressing() ){paste(x,y,HowToPaste::rehearsal );}
          else if(mouse.left.test_unpressed()){paste(x,y,HowToPaste::production_with_overwrite);}
          break;
      case(PaintingMode::layer):
               if(mouse.left.test_pressing() ){paste(x,y,HowToPaste::rehearsal );}
          else if(mouse.left.test_unpressed()){paste(x,y,HowToPaste::production);}
          break;
        }
    }

  else
    if(mouse.right.test_pressing())
    {
CANCEL:
      composing_flag = false;

      point0.x = -1;
      point1.x = -1;
    }

  else
    if(mouse.left.test_pressing())
    {
        if(selecting_state == 2)
        {
          move_corner(x,y);
        }

      else
        {
          make_pointing(x,y);
        }
    }

  else
    if(mouse.left.test_unpressed())
    {
        switch(mode)
        {
      case(PaintingMode::draw_line):
          target->prepare_new_log();

          drawing::draw_line(target,scard_cb,current_color,point0,point1);

          target->prepare_new_log(true);

          goto CANCEL;
          break;
      case(PaintingMode::draw_rect):
          target->prepare_new_log();

          drawing::draw_rect(target,scard_cb,current_color,operating_rect);

          target->prepare_new_log(true);

          goto CANCEL;
          break;
      case(PaintingMode::fill_rect):
          target->prepare_new_log();

          drawing::fill_rect(target,scard_cb,current_color,operating_rect);

          target->prepare_new_log(true);

          goto CANCEL;
          break;
      case(PaintingMode::transform_area_frame):
          selecting_state = 2;

          rect_corner = Corner::none;
          break;
        }
    }


  need_to_redraw();

  callback(nullptr);
}




void
Painter::
draw_selecting_rect()
{
  auto&  pt = content.point;

  const auto&  rect = operating_rect;

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

  constexpr int  w = SuperCard::width ;
  constexpr int  h = SuperCard::height;

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


  target->draw(*this,pt.x,pt.y,pixel_size);

    if(selecting_state)
    {
      draw_selecting_rect();
    }

  else
    if(composing_flag)
    {
      temporary_clip.draw(*this,pt.x,pt.y,pixel_size);
    }
}




