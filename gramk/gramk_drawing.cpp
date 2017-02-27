#include"gramk_drawing.hpp"
#include<cstring>
#include<algorithm>




void
draw_line(const oat::Point&  p0, const oat::Point&  p1, std::vector<oat::Point>&  buf)
{
//http://members.chello.at/~easyfilter/bresenham.htmlから引用
  int  x0 = p0.x;
  int  y0 = p0.y;
  int  x1 = p1.x;
  int  y1 = p1.y;

  const int  x_dist =  std::abs(x1-x0);
  const int  y_dist = -std::abs(y1-y0);
  const int  x_vector = (x0 < x1)? 1:-1;
  const int  y_vector = (y0 < y1)? 1:-1; 

  int  err = x_dist+y_dist;

    for(;;)
    {
      buf.emplace_back(x0,y0);

        if((x0 == x1) &&
           (y0 == y1))
        {
          break;
        }


      const int  e2 = 2*err;

        if(e2 >= y_dist){  err += y_dist;  x0 += x_vector;}
        if(e2 <= x_dist){  err += x_dist;  y0 += y_vector;}
    }
}


void
draw_ellipse(const oat::Point&  p0, const oat::Point&  p1, std::vector<oat::Point>&  buf)
{
//http://members.chello.at/~easyfilter/bresenham.htmlから引用
  int  x0 = p0.x;
  int  y0 = p0.y;
  int  x1 = p1.x;
  int  y1 = p1.y;

   int a = std::abs(x1-x0), b = std::abs(y1-y0), b1 = b&1; /* values of diameter */
   long dx = 4*(1-a)*b*b, dy = 4*(b1+1)*a*a; /* error increment */
   long err = dx+dy+b1*a*a, e2; /* error of 1.step */

   if (x0 > x1) { x0 = x1; x1 += a; } /* if called with swapped points */
   if (y0 > y1) y0 = y1; /* .. exchange them */
   y0 += (b+1)/2; y1 = y0-b1;   /* starting pixel */
   a *= 8*a; b1 = 8*b*b;

   do {
       buf.emplace_back(x1, y0); /*   I. Quadrant */
       buf.emplace_back(x0, y0); /*  II. Quadrant */
       buf.emplace_back(x0, y1); /* III. Quadrant */
       buf.emplace_back(x1, y1); /*  IV. Quadrant */
       e2 = 2*err;
       if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */ 
       if (e2 >= dx || 2*err > dy) { x0++; x1--; err += dx += b1; } /* x step */
   } while (x0 <= x1);
   
   while (y0-y1 < b) {  /* too early stop of flat ellipses a=1 */
       buf.emplace_back(x0-1, y0); /* -> finish tip of ellipse */
       buf.emplace_back(x1+1, y0++); 
       buf.emplace_back(x0-1, y1);
       buf.emplace_back(x1+1, y1--); 
   }
}




