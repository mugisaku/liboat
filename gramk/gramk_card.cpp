#include"gramk_card.hpp"
#include"gramk_painter.hpp"
#include<cstring>




void
Card::
transfer(const Card&  src, const Rect&  src_rect,
               Card&  dst, int  dst_x, int  dst_y, bool  overwrite)
{
    for(int  yy = 0;  yy < src_rect.h;  ++yy)
    {
        if((dst_y+yy) >= height)
        {
          break;
        }


        for(int  xx = 0;  xx < src_rect.w;  ++xx)
        {
            if((dst_x+xx) >= width)
            {
              break;
            }


          auto  v = src.get_color(src_rect.x+xx,src_rect.y+yy);

            if(overwrite || (v&8))
            {
              dst.put_color(v,dst_x+xx,dst_y+yy);
            }
        }
    }
}




Card::
Card(bool  rec):
recording_flag(rec)
{
  clear(false);
}


Card::
Card(const Card&  rhs)
{
  *this = rhs;
}




Card&
Card::
operator=(const Card&  rhs)
{
  std::memcpy(&color_table,&rhs.color_table,sizeof(color_table));

  recording_flag = rhs.recording_flag;

  return *this;
}




uint8_t  Card::get_color(int  x, int  y) const{return color_table[y][x];}


void
Card::
put_color(uint8_t  color, int  x, int  y)
{
  auto&  now = color_table[y][x];

    if(now != color)
    {
        if(recording_flag)
        {
          operation_log.emplace_back(Dot(now,x,y));
        }


      now = color;
    }
}


void
Card::
clear(bool  perfectly)
{
    if(!perfectly)
    {
      prepare_new_log();
    }


  std::memset(&color_table,0,sizeof(color_table));

    if(!perfectly)
    {
      prepare_new_log(true);
    }

  else
    {
      log_list.clear();

      operation_log.clear();
    }
}




void
Card::
render(oat::Widget&  dst, int  x, int  y, int  w, int  h, int  pixel_size) const
{
    for(int  yy = 0;  yy < h;  ++yy){
    for(int  xx = 0;  xx < w;  ++xx){
      auto  v = get_color(xx,yy);

        if(v&8)
        {
          dst.fill_rect(palette[v&7],x+(pixel_size*xx),y+(pixel_size*yy),pixel_size,pixel_size);
        }

      else
        {
          dst.fill_rect(oat::const_color::blue,x+(pixel_size*xx),y+(pixel_size*yy),pixel_size,pixel_size);
        }
    }}
}




 

