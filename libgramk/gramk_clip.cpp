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


void
Clip::
put(const Clip&  src, int  x, int  y)
{
    for(int  yy = 0;  yy < src.get_height();  ++yy)
    {
        if(y+yy >= height)
        {
          break;
        }


        for(int  xx = 0;  xx < src.get_width();  ++xx)
        {
            if(x+xx >= width)
            {
              break;
            }


          auto  v = src.get(xx,yy);

          Card::put(v,x+xx,y+yy);
        }
    }
}




