#include"gramk_supercard.hpp"
#include<cstring>




namespace{


bool
table[80][80];


}


void
SuperCard::
subroutine_for_fill_area(int  color, int  x, int  y, int  target)
{
  auto&  e = table[y][x];

    if(!e)
    {
      e = true;

        if(Card::get(x,y) == target)
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
SuperCard::
fill_area(int  color, int  x, int  y)
{
  auto  target = Card::get(x,y);

    if(target != color)
    {
      std::memset(&table,0,sizeof(table));

      prepare_new_log();

      subroutine_for_fill_area(color,x,y,target);

      prepare_new_log(true);
    }
}




