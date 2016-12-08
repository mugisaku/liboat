#include"mg_area_selection.hpp"
#include"mg_image.hpp"
#include<cstring>
#include<cstdio>




namespace area_selection{


namespace{


Rect
rect;

struct
{
  int*  x;
  int*  y;

} pointer;


}


const Rect&
get_rect()
{
  return rect;
}


bool
test_whether_transformed()
{
  return(pointer.x);
}


void
reset(int  w, int  h)
{
  rect.left   = 0;
  rect.top    = 0;
  rect.right  = w-1;
  rect.bottom = h-1;

  release();
}


void
grab(int  x, int  y)
{
       if((y >= rect.top   ) && (y < (   rect.top+1))){pointer.y = &rect.top;}
  else if((y >= rect.bottom) && (y < (rect.bottom+1))){pointer.y = &rect.bottom;}

       if((x >= rect.left ) && (x < ( rect.left+1))){pointer.x = &rect.left;}
  else if((x >= rect.right) && (x < (rect.right+1))){pointer.x = &rect.right;}


    if(!pointer.x ||
       !pointer.y)
    {
      release();
    }
}


void
move(int  x, int  y)
{
    if(pointer.x &&
       pointer.y)
    {
      *pointer.x = x;
      *pointer.y = y;

        if(rect.left == rect.right)
        {
            if(!rect.left){rect.right =  rect.left+1;}
          else            { rect.left = rect.right-1;}
        }

      else
        if(rect.left > rect.right)
        {
          std::swap(rect.left,rect.right);
        }


        if(rect.top == rect.bottom)
        {
            if(!rect.top){rect.bottom =    rect.top+1;}
          else           {   rect.top = rect.bottom-1;}
        }

      else
        if(rect.top > rect.bottom)
        {
          std::swap(rect.top,rect.bottom);
        }
    }
}


void
release()
{
  pointer.x = nullptr;
  pointer.y = nullptr;
}


}




