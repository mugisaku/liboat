#include"mkqbf_editor.hpp"
#include"mkqbf_core.hpp"




Editor::
Editor()
{
  change_content_width( core::chip_size*core::table_size);
  change_content_height(core::chip_size*core::table_size);

  style.background_color = oat::const_color::green;
}




void
Editor::
process_mouse(const oat::Mouse&  mouse)
{
  cursor = get_mouse_point(mouse);

  cursor.x /= core::chip_size;
  cursor.y /= core::chip_size;

    if(mouse.left.test_pressing())
    {
      core::change_square(cursor.x,cursor.y,true);
    }

  else
    if(mouse.right.test_pressing())
    {
      core::change_square(cursor.x,cursor.y,false);
    }


  need_to_redraw();
}




void
Editor::
draw_digit(int  d, const oat::Color&  color, int  x, int  y)
{
  using Glyph = uint8_t[8];

  constexpr Glyph  digit_glyph[] =
  {
    {0x00,0x3E,0x63,0x63,0x63,0x63,0x63,0x3E,},
    {0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F,},
    {0x00,0x3E,0x63,0x07,0x0E,0x1C,0x38,0x7F,},
    {0x00,0x3E,0x63,0x03,0x1E,0x03,0x63,0x3E,},
    {0x00,0x06,0x0E,0x1E,0x36,0x66,0x7F,0x06,},
    {0x00,0x7F,0x60,0x60,0x7E,0x03,0x63,0x3E,},
    {0x00,0x3E,0x73,0x60,0x7E,0x63,0x63,0x3E,},
    {0x00,0x7F,0x03,0x06,0x0C,0x18,0x30,0x30,},
    {0x00,0x3E,0x63,0x63,0x3E,0x63,0x63,0x3E,},
    {0x00,0x3E,0x63,0x63,0x3F,0x03,0x63,0x3E,},
  };


  const uint8_t*  p = digit_glyph[d];

    for(int  yy = 0;  yy < 8;  yy += 1)
    {
      auto  c = *p++;

        for(int  xx = 0;  xx < 8;  xx += 1)
        {
            if(c&0x80)
            {
              draw_dot(color,x+xx,y+yy);
            }


          c <<= 1;
        }
    }
}


void
Editor::
draw_chip(const oat::Point&  chip_point, int  x_base, int  y_base)
{
    for(int  yy = 0;  yy < core::chip_size;  yy += 1){
    for(int  xx = 0;  xx < core::chip_size;  xx += 1){
      oat::Color  color;

        if(core::get_image_pixel(color,core::chip_size*chip_point.x+xx,
                                       core::chip_size*chip_point.y+yy))
        {
          draw_dot(color,x_base+xx,
                         y_base+yy);
        }
    }}
}


void
Editor::
draw_attribute(int  attr, int  x_base, int  y_base)
{
  fill_rect(oat::const_color::white,x_base+4,
                                    y_base+12,16,8);

  auto  d = (attr&0x7F);

  auto  color = (attr&enterable_flag)? oat::const_color::blue
                                     : oat::const_color::red;

  int  d1 = d/10;

  d %= 10;

  draw_digit(d1,color,x_base+4,
                      y_base+12);

  draw_digit(d ,color,x_base+12,
                      y_base+12);
  draw_digit(d ,color,x_base+12,
                      y_base+12);
}


void
Editor::
draw_bg1()
{
  auto  pt = content.point;

    for(int  y = 0;  y < core::table_size;  y += 1){
    for(int  x = 0;  x < core::table_size;  x += 1){
      auto&  sq = core::get_square(x,y);

      draw_chip(sq.lower,
                pt.x+core::chip_size*x,
                pt.y+core::chip_size*y);
    }}
}


void
Editor::
draw_bg2(bool  with_attribute)
{
  auto  pt = content.point;

    for(int  y = 0;  y < core::table_size;  y += 1){
    for(int  x = 0;  x < core::table_size;  x += 1){
      auto&  sq = core::get_square(x,y);

      const int  x_base = pt.x+core::chip_size*x;
      const int  y_base = pt.y+core::chip_size*y;

      draw_chip(sq.lower,x_base,y_base);
      draw_chip(sq.upper,x_base,y_base);

        if(with_attribute)
        {
          draw_attribute(sq.attribute,x_base,y_base);
        }
   }}
}


void
Editor::
draw_bg3()
{
  auto  pt = content.point;

    for(int  y = 0;  y < core::table_size;  y += 1){
    for(int  x = 0;  x < core::table_size;  x += 1){
      auto&  sq = core::get_square(x,y);

      const int  x_base = pt.x+core::chip_size*x;
      const int  y_base = pt.y+core::chip_size*y;

      draw_attribute(sq.attribute,x_base,y_base);
   }}
}


void
Editor::
render()
{
  fill();

  auto  pt = content.point;

  auto  prc = core::get_process();

    if(prc == core::Process::arrange_lower_chip)
    {
      draw_bg1();
    }

  else
    if(prc == core::Process::arrange_upper_chip)
    {
      draw_bg2(false); 
    }

  else
    {
      draw_bg2(true); 
    }


  draw_rect(oat::const_color::red,pt.x+(core::chip_size*cursor.x),
                                  pt.y+(core::chip_size*cursor.y),
                                  core::chip_size,
                                  core::chip_size);
}




