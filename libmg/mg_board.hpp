#ifndef MG_BOARD_HPP_INCLUDED
#define MG_BOARD_HPP_INCLUDED


#include"oat.hpp"




namespace board{


constexpr int  noentry_flag = 0x80;


struct
Square
{
  int  attribute=0;

  oat::Point  lower;
  oat::Point  upper;

};


namespace Process{
constexpr int  arrange_lower_chip   = 0;
constexpr int  arrange_upper_chip   = 1;
constexpr int  change_attribute     = 2;
constexpr int  transform_area_frame = 3;
}


constexpr int  table_size = 12;


const Square&  get_square(int  x, int  y);
void           put_square(const Square&  sq, int  x, int  y);


void  change_path_text(std::u16string&&  s);

void   read(const char*  path);
void  write();


oat::Widget*  create_widget();


}



#endif




