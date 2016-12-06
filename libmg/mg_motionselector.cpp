#include"mg_motionselector.hpp"
#include"mg_image.hpp"
#include"mg_color_selection.hpp"
#include"mg_message.hpp"




using namespace oat;


MotionSelector::
MotionSelector()
{
  change_content_width( image::get_chip_width()*image::get_chip_number());
  change_content_height(image::get_chip_height());

  style.background_color = const_color::blue;
}




void
MotionSelector::
process_mouse(const Mouse&  mouse)
{
  auto  pt = get_mouse_point(mouse);

    if(mouse.left.test_pressing())
    {
      image::change_chip_index(pt.x/image::get_chip_width());
    }
}


void
MotionSelector::
render()
{
  fill();


  auto  pt = content.point;

  auto  w = image::get_chip_width()*image::get_chip_number();

    for(int  y = 0;  y < image::get_chip_height();  ++y){
    for(int  x = 0;  x < w;                        ++x){
      auto  v = image::get_frame_pixel(x,y);

        if(v&8)
        {
          draw_dot(color_selection::table[v&7],pt.x+x,pt.y+y);
        }
    }}


  auto  x_base = image::get_chip_width()*image::get_chip_index();

  draw_rect(const_color::white,pt.x+x_base,
                               pt.y,image::get_chip_width(),image::get_chip_height());
}




