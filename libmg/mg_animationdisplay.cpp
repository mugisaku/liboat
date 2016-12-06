#include"mg_animationdisplay.hpp"
#include"mg_color_selection.hpp"
#include"mg_image.hpp"




constexpr int  pixel_size = 4;




AnimationDisplay::
AnimationDisplay():
phase(0)
{
  change_content_width( image::get_chip_width() *pixel_size);
  change_content_height(image::get_chip_height()*pixel_size);
}




void
AnimationDisplay::
check(uint32_t  now)
{
  static uint32_t  last;

    if(now >= last+200)
    {
      last = now;

      phase += 1;

        if(phase >= 4)
        {
          phase = 0;
        }


      need_to_redraw();
    }
}


void
AnimationDisplay::
render()
{
  fill();

  auto  pt = content.point;

  static int  bases[] = {0,1,0,2};

  const int  w = image::get_chip_width();
  const int  h = image::get_chip_height();

  int  x_base = w*bases[phase];

    for(int  y = 0;  y < h;  y += 1){
    for(int  x = 0;  x < w;  x += 1){
      auto  v = image::get_frame_pixel(x_base+x,y);

        if(v&8)
        {
          fill_rect(color_selection::table[v&7],pt.x+(pixel_size*x),
                                                pt.y+(pixel_size*y),pixel_size,pixel_size);
        }
    }}
}




