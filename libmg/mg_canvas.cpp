#include"mg_canvas.hpp"
#include"mg_colorselector.hpp"
#include"mg_core.hpp"
#include<cstring>



constexpr int  pixel_size = 10;


Canvas::
Canvas(bool  grid_extent_):
grid_extent(grid_extent_)
{
  core::selection::reset();


  change_content_width( core::get_chip_width() *pixel_size);
  change_content_height(core::get_chip_height()*pixel_size);

  style.background_color = oat::const_color::blue;
}




void
Canvas::
process_mouse(const oat::Mouse&  mouse)
{
  auto  pt = get_mouse_point(mouse);

  int  x = pt.x/pixel_size;
  int  y = pt.y/pixel_size;

    switch(core::get_tool_index())
    {
  case(core::Tool::draw_point):
        if(mouse.left.test_pressing())
        {
          core::put_pixel(core::get_color_index()|8,x,y);
        }

      else
        if(mouse.right.test_pressing())
        {
          core::put_pixel(0,x,y);
        }
      break;
  case(core::Tool::fill_area):
        if(mouse.left.test_pressing())
        {
          core::fill_area(core::get_color_index()|8,x,y);
        }

      else
        if(mouse.right.test_pressing())
        {
          core::fill_area(0,x,y);
        }
      break;
  case(core::Tool::transform_selection_frame):
        if(mouse.left.test_pressed())
        {
          core::selection::grab(x,y);
        }

      else
        if(mouse.left.test_pressing())
        {
          core::selection::move(x,y);

          core::set_modified_flag(core::canvas_modified_flag);
        }

      else
        if(mouse.right.test_pressing())
        {
        }
      break;
  case(core::Tool::paste):
        if(mouse.left.test_pressing())
        {
          core::paste_chip(x,y,true);
        }
      break;
  case(core::Tool::layer):
        if(mouse.left.test_pressing())
        {
          core::paste_chip(x,y,false);
        }
      break;
    }
}




void
Canvas::
draw_selection_frame()
{
  auto&  pt = content.point;

  auto&  rect = core::selection::get_rect();

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
}


void
Canvas::
render()
{
  fill();


  auto  pt = content.point;

  constexpr oat::Color  l1(0x7F,0x7F,0x0);
  constexpr oat::Color  l2(0xFF,0xFF,0x00);

  const int  w = core::get_chip_width();
  const int  h = core::get_chip_height();

    for(int  y = 0;  y < h;  y += 1)
    {
        for(int  x = 0;  x < w;  x += 1)
        {
          auto  v = core::get_chip_pixel(x,y);

            if(v&8)
            {
              fill_rect(::palette[v&7],pt.x+(pixel_size*x),
                                       pt.y+(pixel_size*y),pixel_size,pixel_size);
            }


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



    if(grid_extent)
    {
      draw_rect(l2,pt.x+pixel_size*4+1,
                   pt.y+pixel_size*4+1,
                   pixel_size*(w-8),
                   pixel_size*(h-8));
    }


    if((core::get_tool_index() == core::Tool::transform_selection_frame) ||
       core::selection::test_whether_transformed())
    {
      draw_selection_frame();
    }
}




