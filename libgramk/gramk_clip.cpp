#include"gramk_clip.hpp"
#include<cstring>




void
Clip::
change_size(int  w, int  h)
{
  width  = w;
  height = h;
}


int  Clip::get_width()  const{return width;}
int  Clip::get_height() const{return height;}

uint8_t  Clip::get(                int  x, int  y) const{return pixels[y][x];}
void     Clip::put(uint8_t  pixel, int  x, int  y)      {pixels[y][x] = pixel;}


void  Clip::clear(){std::memset(&pixels,0,sizeof(pixels));}




