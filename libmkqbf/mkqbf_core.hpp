#ifndef MG_CORE_HPP_INCLUDED
#define MG_CORE_HPP_INCLUDED


#include<cstdint>
#include<memory>
#include"oat_widget.hpp"




constexpr int  enterable_flag = 0x80;


struct
Square
{
  int  attribute=0;

  oat::Point  lower;
  oat::Point  upper;

};


namespace core{


namespace Process{
constexpr int  arrange_lower_chip = 0;
constexpr int  arrange_upper_chip = 1;
constexpr int  change_attribute   = 2;
}


namespace Update{
constexpr int  table_flag = 1;
constexpr int  image_flag = 2;
}


constexpr int  table_size = 12;
constexpr int   chip_size = 24;
constexpr int  image_color_number = 16;
constexpr int  image_size = 24*16;


Square&  get_square(int  x, int  y);

void  change_square(int  x, int  y, bool  flag);

bool  get_image_pixel(oat::Color&  color, int  x, int  y);


void  change_index(int  v);


void  change_chip_point(int  x, int  y);
oat::Point     get_chip_point();


void  change_process(int  v);
int      get_process();

void  step_display();
bool  test_display();

void  set_modified_flag(int  flag);
int   get_modified_flags();


const char*  get_filepath();

void   read(const char*  path);
void  write();


}



#endif




