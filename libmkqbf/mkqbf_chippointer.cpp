#include"mkqbf_chippointer.hpp"
#include"mkqbf_core.hpp"




ChipPointer::
ChipPointer()
{
  change_content_width( core::image_size);
  change_content_height(core::image_size);

  style.background_color = oat::const_color::blue;
}




void
ChipPointer::
process_mouse(const oat::Mouse&  mouse)
{
  cursor = get_mouse_point(mouse);

  cursor.x /= core::chip_size;
  cursor.y /= core::chip_size;

    if(mouse.left.test_pressing())
    {
      core::change_chip_point(cursor.x,cursor.y);
    }


  need_to_redraw();
}




void
ChipPointer::
render()
{
  fill();

  auto  pt = content.point;

    for(int  y = 0;  y < core::image_size;  y += 1){
    for(int  x = 0;  x < core::image_size;  x += 1){
      draw_dot(core::get_image_pixel(x,y),pt.x+x,
                                          pt.y+y);
    }}


  draw_rect(oat::const_color::red,pt.x+(core::chip_size*cursor.x),
                                  pt.y+(core::chip_size*cursor.y),
                                  core::chip_size,
                                  core::chip_size);


  auto  chppt = core::get_chip_point();

  draw_rect(oat::const_color::green,pt.x+(core::chip_size*chppt.x),
                                    pt.y+(core::chip_size*chppt.y),
                                  core::chip_size,
                                  core::chip_size);

  draw_rect(oat::const_color::yellow,pt.x+(core::chip_size*chppt.x)+1,
                                     pt.y+(core::chip_size*chppt.y)+1,
                                  core::chip_size-2,
                                  core::chip_size-2);
}




