#include"gramk_card.hpp"
#include<cstring>




namespace{


bool
table[80][80];


}


void
Card::
subroutine_for_fill_area(int  color, int  x, int  y, int  target)
{
  auto&  e = table[y][x];

    if(!e)
    {
      e = true;

        if(get(x,y) == target)
        {
          put(color,x,y);

            if(x             ){subroutine_for_fill_area(color,x-1,y  ,target);}
            if(y             ){subroutine_for_fill_area(color,x  ,y-1,target);}
            if(x < (width -1)){subroutine_for_fill_area(color,x+1,y  ,target);}
            if(y < (height-1)){subroutine_for_fill_area(color,x  ,y+1,target);}
        }
    }
}



void
Card::
fill_area(int  color, int  x, int  y)
{
  auto  target = get(x,y);

    if(target != color)
    {
      std::memset(&table,0,sizeof(table));

      prepare_new_log();

      subroutine_for_fill_area(color,x,y,target);

      prepare_new_log(true);
    }
}




