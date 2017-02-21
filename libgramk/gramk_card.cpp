#include"gramk_card.hpp"
#include"gramk_clip.hpp"
#include"gramk_painter.hpp"
#include<cstring>




Card::
Card()
{
  std::memset(&pixels,0,sizeof(pixels));
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
  std::memcpy(&pixels,&rhs.pixels,sizeof(pixels));

  return *this;
}




void
Card::
put(int  color, int  x, int  y)
{
  auto&  now = pixels[y][x];

    if(now != color)
    {
      operation_log.emplace_back(Dot(now,x,y));

      now = color;
    }
}


void
Card::
put_without_logging(int  color, int  x, int  y)
{
  pixels[y][x] = color;
}


void
Card::
put(const Clip&  clip, int  x, int  y, bool  overwrite)
{
    for(int  yy = 0;  yy < clip.get_height();  ++yy)
    {
        if(y+yy >= height)
        {
          break;
        }


        for(int  xx = 0;  xx < clip.get_width();  ++xx)
        {
            if(x+xx >= width)
            {
              break;
            }


          auto  v = clip.get(xx,yy);

            if(overwrite || (v&8))
            {
              put(v,x+xx,y+yy);
            }
        }
    }
}


uint8_t
Card::
get(int  x, int  y) const
{
  return pixels[y][x];
}


void
Card::
draw_rect(int  color, int  x, int  y, int  w, int  h)
{
    for(int  xx = 0;  xx < w;  ++xx)
    {
      put(color,x+xx,y    );
      put(color,x+xx,y+h-1);
    }


    for(int  yy = 1;  yy < h-1;  ++yy)
    {
      put(color,x    ,y);
      put(color,x+w-1,y);
    }
}


void
Card::
fill_rect(int  color, int  x, int  y, int  w, int  h)
{
    for(int  yy = 0;  yy < h;  ++yy){
    for(int  xx = 0;  xx < w;  ++xx){
      put(color,x+xx,y+yy);
    }}
}


void
Card::
get(Clip&  clip, int  x, int  y, int  w, int  h) const
{
    if(!w){w =  width;}
    if(!h){h = height;}


    for(int  yy = 0;  yy < h;  ++yy){
    for(int  xx = 0;  xx < w;  ++xx){
      clip.put(get(x+xx,y+yy),xx,yy);
    }}
}


void
Card::
revolve(int  x, int  y, int  w, int  h)
{
  Card  tmp = *this;

  w = std::min(w,h);

  prepare_new_log();

    for(int  yy = 0;  yy < w;  ++yy){
    for(int  xx = 0;  xx < w;  ++xx){
      put(tmp.get(x+xx,y+yy),x+w-1-yy,y+xx);
    }}


  prepare_new_log(true);
}


void
Card::
reverse_horizontally(int  x, int  y, int  w, int  h)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < h;  ++yy){
    for(int  xx = 0;  xx < w;  ++xx){
      put(tmp.get(x+xx,y+yy),x+xx,y+h-1-yy);
    }}


  prepare_new_log(true);
}


void
Card::
reverse_vertically(int  x, int  y, int  w, int  h)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < h;  ++yy){
    for(int  xx = 0;  xx < w;  ++xx){
      put(tmp.get(x+xx,y+yy),x+w-1-xx,y+yy);
    }}


  prepare_new_log(true);
}


void
Card::
mirror_vertically(int  x, int  y, int  w, int  h)
{
  prepare_new_log();

    for(int  yy = 0;  yy < h  ;  ++yy){
    for(int  xx = 0;  xx < w/2;  ++xx){
      auto  v = get(x+xx,y+yy);

      put(v,x+w-1-xx,y+yy);
    }}


  prepare_new_log(true);
}


void
Card::
clear()
{
  prepare_new_log();

    for(int  y = 0;  y < height;  ++y){
    for(int  x = 0;  x < width ;  ++x){
      put(0,x,y);
    }}


  prepare_new_log(true);
}


void
Card::
undo()
{
RESTART:
    if(operation_log.size())
    {
      auto&  dot = operation_log.back();

      pixels[dot.y][dot.x] = dot.color;

      operation_log.pop_back();
    }

  else
    if(!log_list.empty())
    {
      auto&  log = log_list.front();

        if(log.solid_flag)
        {
          auto   it = log.stack.crbegin();
          auto  end = log.stack.crend();

            while(it != end)
            {
              pixels[it->y][it->x] = it->color;

              ++it;
            }


          log_list.pop_front();
        }

      else
        {
          operation_log = std::move(log.stack);

          log_list.pop_front();

          goto RESTART;
        }
    }
}


void
Card::
prepare_new_log(bool  solid_flag)
{
    if(operation_log.size())
    {
      log_list.emplace_front(std::move(operation_log),solid_flag);

      operation_log.clear();
    }
}


void
Card::
draw(oat::Widget&  dst, int  x, int  y) const
{
    for(int  yy = 0;  yy < height;  ++yy){
    for(int  xx = 0;  xx <  width;  ++xx){
      auto  v = get(xx,yy);

        if(v)
        {
          dst.draw_dot(palette[v&7],x+xx,y+yy);
        }
    }}
}




