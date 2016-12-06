#ifndef MG_COLOR_SELECTION_HPP_INCLUDED
#define MG_COLOR_SELECTION_HPP_INCLUDED


#include"oat.hpp"




namespace color_selection{


constexpr int  element_number = 8;


constexpr oat::Color
table[element_number] =
{
  oat::Color(0x1F),
  oat::Color(0x3F),
  oat::Color(0x5F),
  oat::Color(0x7F),
  oat::Color(0x9F),
  oat::Color(0xBF),
  oat::Color(0xDF),
  oat::Color(0xFF),
};


void  change_index(int  v);
int   get_index();


oat::Widget*  create_widget();


}



#endif




