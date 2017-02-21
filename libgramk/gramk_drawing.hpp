#ifndef GRAMK_DRAWING_HPP_INCLUDED
#define GRAMK_DRAWING_HPP_INCLUDED




namespace drawing{


using Callback = void  (*)(void*  that, int  color, int  x, int  y);

void  draw_line(void*  that, Callback  callback, int  color, int  x0, int  y0, int  x1, int  y1);


}




#endif




