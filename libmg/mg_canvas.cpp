#include"mg_canvas.hpp"
#include"mg_image.hpp"
#include"mg_message.hpp"
#include"mg_area_selection.hpp"
#include"mg_color_selection.hpp"
#include"mg_tool_selection.hpp"
#include<cstring>



constexpr int  pixel_size = 10;


Canvas::
Canvas(bool  grid_extent_):
grid_extent(grid_extent_)
{
  area_selection::reset();


  change_content_width( image::get_chip_width() *pixel_size);
  change_content_height(image::get_chip_height()*pixel_size);

  style.background_color = oat::const_color::blue;
}




void
Canvas::
process_mouse(const oat::Mouse&  mouse)
{
  auto  pt = get_mouse_point(mouse);

  int  x = pt.x/pixel_size;
  int  y = pt.y/pixel_size;

    switch(tool_selection::get_index())
    {
  case(tool_selection::draw_point):
        if(mouse.left.test_pressing())
        {
          image::put_pixel(color_selection::get_index()|8,x,y);

          message::set_flag(message::image_modified_flag);
        }

      else
        if(mouse.right.test_pressing())
        {
          image::put_pixel(0,x,y);

          message::set_flag(message::image_modified_flag);
        }
      break;
  case(tool_selection::fill_area):
        if(mouse.left.test_pressing())
        {
          image::fill_area(color_selection::get_index()|8,x,y);

          message::set_flag(message::image_modified_flag);
        }

      else
        if(mouse.right.test_pressing())
        {
          image::fill_area(0,x,y);

          message::set_flag(message::image_modified_flag);
        }
      break;
  case(tool_selection::transform_area_frame):
        if(mouse.left.test_pressed())
        {
          area_selection::grab(x,y);
        }

      else
        if(mouse.left.test_pressing())
        {
          area_selection::move(x,y);

          message::set_flag(message::image_modified_flag);
        }
      break;
  case(tool_selection::paste):
        if(mouse.left.test_pressing())
        {
          image::paste_chip(x,y,true);

          message::set_flag(message::image_modified_flag);
        }
      break;
  case(tool_selection::layer):
        if(mouse.left.test_pressing())
        {
          image::paste_chip(x,y,false);

          message::set_flag(message::image_modified_flag);
        }
      break;
    }
}




void
Canvas::
draw_selection_frame()
{
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
}


void
Canvas::
render()
{
  fill();


  auto  pt = content.point;

  constexpr oat::Color  l1(0x7F,0x7F,0x0);
  constexpr oat::Color  l2(0xFF,0xFF,0x00);

  const int  w = image::get_chip_width();
  const int  h = image::get_chip_height();

    for(int  y = 0;  y < h;  y += 1)
    {
        for(int  x = 0;  x < w;  x += 1)
        {
          auto  v = image::get_chip_pixel(x,y);

            if(v&8)
            {
              fill_rect(color_selection::table[v&7],pt.x+(pixel_size*x),
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


    if((tool_selection::get_index() == tool_selection::transform_area_frame) ||
        area_selection::test_whether_transformed())
    {
      draw_selection_frame();
    }
}




