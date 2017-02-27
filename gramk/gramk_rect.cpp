#include"gramk_rect.hpp"
#include<algorithm>




void
Rect::
form(const oat::Point&  p0, const oat::Point&  p1)
{
  const int  x_min = std::min(p0.x,p1.x);
  const int  x_max = std::max(p0.x,p1.x);
  const int  y_min = std::min(p0.y,p1.y);
  const int  y_max = std::max(p0.y,p1.y);

  x =       x_min;
  y =       y_min;
  w = x_max-x_min+1;
  h = y_max-y_min+1;
}




void
Rect::
draw(std::vector<oat::Point>&  buf) const
{
    for(int  xx = 0;  xx < w;  ++xx)
    {
      buf.emplace_back(x+xx,y    );
      buf.emplace_back(x+xx,y+h-1);
    }


    for(int  yy = 1;  yy < h-1;  ++yy)
    {
      buf.emplace_back(x    ,y+yy);
      buf.emplace_back(x+w-1,y+yy);
    }
}


void
Rect::
fill(std::vector<oat::Point>&  buf) const
{
    for(int  yy = 0;  yy < h;  ++yy){
    for(int  xx = 0;  xx < w;  ++xx){
      buf.emplace_back(x+xx,y+yy);
    }}
}





