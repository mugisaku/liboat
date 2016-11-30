#include"mkqbf_editor.hpp"
#include"mkqbf_core.hpp"




Editor::
Editor()
{
  change_content_width( core::chip_size*core::table_size);
  change_content_height(core::chip_size*core::table_size);

  style.background_color = oat::const_color::blue;
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
render()
{
  fill();

  auto  pt = content.point;

  auto  prc = core::get_process();

  auto  v = core::test_display();

    for(int  y = 0;  y < core::table_size;  y += 1){
    for(int  x = 0;  x < core::table_size;  x += 1){
      auto&  sq = core::get_square(x,y);

        if(prc == core::Process::arrange_lower_chip)
        {
            for(int  yy = 0;  yy < core::chip_size;  yy += 1){
            for(int  xx = 0;  xx < core::chip_size;  xx += 1){
              oat::Color  color;

                if(core::get_image_pixel(color,core::chip_size*sq.lower.x+xx,
                                               core::chip_size*sq.lower.y+yy))
                {
                  draw_dot(color,pt.x+core::chip_size*x+xx,
                                 pt.y+core::chip_size*y+yy);
                }


                if(v && sq.upper.x && sq.upper.y)
                {
                    if(core::get_image_pixel(color,core::chip_size*sq.upper.x+xx,
                                                   core::chip_size*sq.upper.y+yy))
                    {
                      draw_dot(color,pt.x+core::chip_size*x+xx,
                                     pt.y+core::chip_size*y+yy);
                    }
               }
            }}
        }

      else
        if((prc == core::Process::arrange_upper_chip) ||
           (v && (prc == core::Process::change_attribute)))
        {
            for(int  yy = 0;  yy < core::chip_size;  yy += 1){
            for(int  xx = 0;  xx < core::chip_size;  xx += 1){
              oat::Color  color;

                if(core::get_image_pixel(color,core::chip_size*sq.lower.x+xx,
                                               core::chip_size*sq.lower.y+yy))
                {
                  draw_dot(color,pt.x+core::chip_size*x+xx,
                                 pt.y+core::chip_size*y+yy);
                }


                if(sq.upper.x && sq.upper.y)
                {
                    if(core::get_image_pixel(color,core::chip_size*sq.upper.x+xx,
                                                   core::chip_size*sq.upper.y+yy))
                    {
                      draw_dot(color,pt.x+core::chip_size*x+xx,
                                     pt.y+core::chip_size*y+yy);
                    }
                }
            }}
        }

      else
        {
          auto  d = (sq.attribute&0x7F);

          auto  color0 = (sq.attribute&enterable_flag)? oat::const_color::white
                                                      : oat::const_color::black;

          auto  color1 = (sq.attribute&enterable_flag)? oat::const_color::black
                                                      : oat::const_color::white;

          fill_rect(color0,pt.x+core::chip_size*x,
                           pt.y+core::chip_size*y,
                           core::chip_size,
                           core::chip_size);

          int  d1 = d/10;

          d %= 10;

          draw_digit(d1,color1,pt.x+core::chip_size*x+4,
                               pt.y+core::chip_size*y+12);
          draw_digit(d ,color1,pt.x+core::chip_size*x+12,
                               pt.y+core::chip_size*y+12);
        }
    }}


  draw_rect(oat::const_color::red,pt.x+(core::chip_size*cursor.x),
                                  pt.y+(core::chip_size*cursor.y),
                                  core::chip_size,
                                  core::chip_size);
}




