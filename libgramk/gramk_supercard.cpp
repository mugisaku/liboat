#include"gramk_supercard.hpp"
#include"gramk_clip.hpp"
#include<cstring>




SuperCard::
SuperCard()
{
}


SuperCard::
SuperCard(const SuperCard&  rhs)
{
  *this = rhs;
}




SuperCard&
SuperCard::
operator=(const SuperCard&  rhs)
{
  std::memcpy(&color_table,&rhs.color_table,sizeof(color_table));

  return *this;
}




void
SuperCard::
put(int  color, int  x, int  y)
{
  auto&  now = color_table[y][x];

    if(now != color)
    {
      operation_log.emplace_back(Dot(now,x,y));

      now = color;
    }
}


void
SuperCard::
put_without_logging(int  color, int  x, int  y)
{
  Card::put(color,x,y);
}


void
SuperCard::
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


void
SuperCard::
get(Clip&  clip, const Rect&  rect) const
{
  int  w = rect.w;
  int  h = rect.h;

    if(!w){w =  width;}
    if(!h){h = height;}


  clip.change_size(w,h);

    for(int  y = 0;  y < h;  ++y){
    for(int  x = 0;  x < w;  ++x){
      clip.Card::put(Card::get(rect.x+x,rect.y+y),x,y);
    }}
}


void
SuperCard::
revolve(const Rect&  rect)
{
  Card  tmp = *this;

  const int  w = std::min(rect.w,rect.h);

  prepare_new_log();

    for(int  yy = 0;  yy < w;  ++yy){
    for(int  xx = 0;  xx < w;  ++xx){
      put(tmp.get(rect.x+xx,rect.y+yy),rect.x+w-1-yy,rect.y+xx);
    }}


  prepare_new_log(true);
}


void
SuperCard::
reverse_horizontally(const Rect&  rect)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < rect.h;  ++yy){
    for(int  xx = 0;  xx < rect.w;  ++xx){
      put(tmp.get(rect.x+xx,rect.y+yy),rect.x+xx,rect.y+rect.h-1-yy);
    }}


  prepare_new_log(true);
}


void
SuperCard::
reverse_vertically(const Rect&  rect)
{
  Card  tmp = *this;

  prepare_new_log();

    for(int  yy = 0;  yy < rect.h;  ++yy){
    for(int  xx = 0;  xx < rect.w;  ++xx){
      put(tmp.get(rect.x+xx,rect.y+yy),rect.x+rect.w-1-xx,rect.y+yy);
    }}


  prepare_new_log(true);
}


void
SuperCard::
mirror_vertically(const Rect&  rect)
{
  prepare_new_log();

    for(int  yy = 0;  yy < rect.h  ;  ++yy){
    for(int  xx = 0;  xx < rect.w/2;  ++xx){
      auto  v = Card::get(rect.x+xx,rect.y+yy);

      put(v,rect.x+rect.w-1-xx,rect.y+yy);
    }}


  prepare_new_log(true);
}


void
SuperCard::
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
SuperCard::
undo()
{
RESTART:
    if(operation_log.size())
    {
      auto&  dot = operation_log.back();

      Card::put(dot.color,dot.x,dot.y);

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
              Card::put(it->color,it->x,it->y);

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
SuperCard::
prepare_new_log(bool  solid_flag)
{
    if(operation_log.size())
    {
      log_list.emplace_front(std::move(operation_log),solid_flag);

      operation_log.clear();
    }
}




