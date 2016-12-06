#include"mg_patterndisplay.hpp"
#include"mg_patterntable.hpp"
#include"mg_color_selection.hpp"
#include"mg_image.hpp"
#include"mg_message.hpp"




constexpr int  pixel_size = 2;




PatternDisplay::
PatternDisplay(PatternTable&  top_, const PatternTable*  bottom_):
top(top_),
bottom(bottom_)
{
  change_content_width( image::get_chip_width() *pixel_size*PatternTable::size);
  change_content_height(image::get_chip_height()*pixel_size*PatternTable::size);

  style.background_color = oat::const_color::blue;
}




void
PatternDisplay::
process_mouse(const oat::Mouse&  mouse)
{
  cursor = get_mouse_point(mouse);

  int  w = image::get_chip_width() *pixel_size;
  int  h = image::get_chip_height()*pixel_size;

  cursor.x /= w;
  cursor.y /= h;

    if(mouse.left.test_pressing())
    {
      top.change(cursor.x,cursor.y);

      need_to_redraw();
    }


  cursor.x *= w;
  cursor.y *= h;
}




void
PatternDisplay::
render_table(const PatternTable&  tbl)
{
  auto  pt = content.point;

  const int  w = image::get_chip_width();
  const int  h = image::get_chip_height();

    for(int  y = 0;  y < PatternTable::size;  y += 1){
    for(int  x = 0;  x < PatternTable::size;  x += 1){
      auto&  ptnpt = tbl.get(x,y);

        for(int  yy = 0;  yy < h;  yy += 1){
        for(int  xx = 0;  xx < w;  xx += 1){
          auto  v = image::get_pixel(ptnpt.x+xx,ptnpt.y+yy);

            if(v&8)
            {
              fill_rect(color_selection::table[v&7],pt.x+(w*pixel_size*x)+(pixel_size*xx),
                                                    pt.y+(h*pixel_size*y)+(pixel_size*yy),pixel_size,pixel_size);
            }
        }}
    }}
}


void
PatternDisplay::
render()
{
  fill();

    if(bottom)
    {
      render_table(*bottom);
    }


  render_table(top);


  auto  pt = content.point;

  draw_rect(oat::const_color::white,pt.x+cursor.x,
                                    pt.y+cursor.y,
                                    (pixel_size*image::get_chip_width()),
                                    (pixel_size*image::get_chip_height()));
}




