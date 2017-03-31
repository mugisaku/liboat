#include"gramk_card.hpp"
#include<cstring>




namespace{


std::vector<uint8_t>
table;


}


void
Card::
subroutine_for_fill_area(int  color, int  x, int  y, int  target)
{
  auto&  e = table[(width*y)+x];

    if(!e)
    {
      e = true;

        if(get_color(x,y) == target)
        {
          put_color(color,x,y);

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
  table.resize(width*height);

  auto  target = get_color(x,y);

    if(target != color)
    {
      std::fill(table.begin(),table.end(),0);

      prepare_new_log();

      subroutine_for_fill_area(color,x,y,target);

      prepare_new_log(true);
    }
}




