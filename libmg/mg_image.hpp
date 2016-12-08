#ifndef MG_IMAGE_HPP_INCLUDED
#define MG_IMAGE_HPP_INCLUDED


#include<cstdint>
#include"oat.hpp"


struct
Frame
{
  int  x;
  int  y;
  int  w;
  int  h;

};


namespace image{


constexpr int  size = 384;


void  set_parameter(int  w, int  h, int  n=1);

int  get_chip_width();
int  get_chip_height();
int  get_chip_index();
int  get_chip_number();


void  change_chip_index(int  v);

int  get_chip_width();
int  get_chip_height();
int  get_chip_index();
int  get_chip_number();

const Frame&  get_frame();

void  change_frame_point(const oat::Point&  pt);




void  put_pixel(int  color_index, int  x, int  y);
void  fill_area(int  color_index_, int  x, int  y);
void  paste_chip(int  x, int  y, bool  overwrite);


oat::Widget*  create_main_widget();
oat::Widget*  create_edit_widget();
oat::Widget*  create_save_widget();




int  get_pixel(int  x, int  y);
int  get_chip_pixel(int  x, int  y);
int  get_frame_pixel(int  x, int  y);


void  change_path_text(std::u16string&&  s);

void   read(const char*  path);
void  write();


}



#endif




