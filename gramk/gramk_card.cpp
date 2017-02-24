#include"gramk_card.hpp"
#include"gramk_supercard.hpp"
#include"gramk_painter.hpp"
#include<cstring>




Card::
Card()
{
  clear();
}


uint8_t  Card::get(                int  x, int  y) const{return color_table[y][x];}
void     Card::put(uint8_t  color, int  x, int  y)      {color_table[y][x] = color;}


void  Card::clear(){std::memset(&color_table,0,sizeof(color_table));}


void
Card::
draw(oat::Widget&  dst, int  x, int  y, int  pixel_size) const
{
    for(int  yy = 0;  yy < fixed_height;  ++yy){
    for(int  xx = 0;  xx < fixed_width ;  ++xx){
      auto  v = get(xx,yy);

        if(v)
        {
          dst.fill_rect(palette[v&7],x+(pixel_size*xx),y+(pixel_size*yy),pixel_size,pixel_size);
        }
    }}
}






