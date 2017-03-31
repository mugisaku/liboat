#include"gramk_card.hpp"
#include"gramk_painter.hpp"
#include<cstring>




Rect
Card::
whole_rect;


int  Card::width ;
int  Card::height;


void
Card::
reset_size(int  w, int  h)
{
  width  = w;
  height = h;

  whole_rect.w = w;
  whole_rect.h = h;
}


void
Card::
transfer(const Card&  src, const Rect&  src_rect,
               Card&  dst, int  dst_x, int  dst_y, bool  overwrite)
{
    for(int  yy = 0;  yy < src_rect.h;  ++yy)
    {
      const int  yyy = (dst_y+yy);

        if(yyy >= height)
        {
          break;
        }


        for(int  xx = 0;  xx < src_rect.w;  ++xx)
        {
          const int  xxx = (dst_x+xx);

            if(xxx >= width)
            {
              break;
            }


          auto  v = src.get_color(src_rect.x+xx,src_rect.y+yy);

            if(overwrite || (v&8))
            {
              dst.put_color(v,xxx,yyy);
            }
        }
    }
}




Card::
Card(bool  rec):
recording_flag(rec)
{
  clear();
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
  clear();

  color_table = rhs.color_table;

  recording_flag = rhs.recording_flag;

  return *this;
}




uint8_t  Card::get_color(int  x, int  y) const{return color_table[(width*y)+x];}


void
Card::
put_color(uint8_t  color, int  x, int  y)
{
  auto&  now = color_table[(width*y)+x];

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
clear()
{
  color_table.resize(width*height);

  std::fill(color_table.begin(),color_table.end(),0);

  log_list.clear();

  operation_log.clear();
}




void
Card::
render(int  src_w, int  src_h, oat::Widget&  dst, int  dst_x, int  dst_y, int  pixel_size) const
{
    for(int  yy = 0;  yy < src_h;  ++yy)
    {
      const int  yyy = dst_y+(pixel_size*yy);

        for(int  xx = 0;  xx < src_w;  ++xx)
        {
          const int  xxx = dst_x+(pixel_size*xx);

          auto  v = get_color(xx,yy);

            if(v&8)
            {
              dst.fill_rect(palette[v&7],xxx,yyy,pixel_size,pixel_size);
            }
        }
    }
}




 

