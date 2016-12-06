#include"mg_patterntable.hpp"
#include"mg_image.hpp"




void
PatternTable::
change(int  x, int  y)
{
  data[y][x].reset(image::get_frame().x,
                   image::get_frame().y);
}


const oat::Point&
PatternTable::
get(int  x, int  y) const
{
  return data[y][x];
}





