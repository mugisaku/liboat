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




