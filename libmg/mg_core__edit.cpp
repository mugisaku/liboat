#include"mg_core.hpp"




namespace core{


namespace{


Frame  copy_frame;
std::vector<uint8_t>  copy_buffer;



std::vector<uint8_t>::const_iterator
copy(const Frame&  frm)
{
  static std::vector<uint8_t>  buffer;

  buffer.clear();
  
    for(int  y = 0;  y < frm.h;  ++y){
    for(int  x = 0;  x < frm.w;  ++x){
      buffer.emplace_back(get_chip_pixel(frm.x+x,frm.y+y));
    }}


  return buffer.cbegin();
}


}




void
copy_chip()
{
  copy_frame = selection::get_rect().to_frame();

  copy_buffer.clear();

    for(int  y = 0;  y < copy_frame.h;  ++y){
    for(int  x = 0;  x < copy_frame.w;  ++x){
      copy_buffer.emplace_back(get_chip_pixel(copy_frame.x+x,copy_frame.y+y));
    }}
}


void
paste_chip(int  x, int  y, bool  overwrite)
{
    if(copy_buffer.size())
    {
      auto  chip_w = get_chip_width();
      auto  chip_h = get_chip_height();

        for(int  yy = 0;  yy < copy_frame.h;  ++yy)
        {
            if(y+yy >= chip_h)
            {
              break;
            }


            for(int  xx = 0;  xx < copy_frame.w;  ++xx)
            {
                if(x+xx >= chip_w)
                {
                  break;
                }


              auto  v = copy_buffer[(copy_frame.w*yy)+xx];

                if(overwrite || (v&8))
                {
                  put_pixel(v,x+xx,y+yy);
                }
            }
        }


      update_because_of_image_changed();
    }
}


void
reverse_chip_horizontally()
{
  auto  frm = selection::get_rect().to_frame();

  auto  it = copy(frm);

    for(int  y = frm.h-1;  y >=    0;  --y){
    for(int  x =       0;  x < frm.w;  ++x){
      put_pixel(*it++,frm.x+x,frm.y+y);
    }}


  update_because_of_image_changed();
}


void
reverse_chip_vertically()
{
  auto  frm = selection::get_rect().to_frame();

  auto  it = copy(frm);

    for(int  y =       0;  y < frm.h;  ++y){
    for(int  x = frm.w-1;  x >=    0;  --x){
      put_pixel(*it++,frm.x+x,frm.y+y);
    }}


  update_because_of_image_changed();
}


void
mirror_chip_vertically()
{
  auto  frm = selection::get_rect().to_frame();

    for(int  y = 0;  y < frm.h;  ++y)
    {
        for(int  x = 0;  x < frm.w/2;  ++x)
        {
          auto  v = get_chip_pixel(frm.x+x,frm.y+y);

          put_pixel(v,frm.x+frm.w-1-x,frm.y+y);
        }
    }


  update_because_of_image_changed();
}




void
shift_chip_up()
{
  auto  frm = selection::get_rect().to_frame();

  auto  it = copy(frm);

  it += frm.w;

    for(int  y = 0;  y < frm.h-1;  ++y){
    for(int  x = 0;  x < frm.w  ;  ++x){
      put_pixel(*it++,frm.x+x,frm.y+y);
    }}


  update_because_of_image_changed();
}


void
shift_chip_left()
{
  auto  frm = selection::get_rect().to_frame();

  auto  it = copy(frm);

    for(int  y = 0;  y < frm.h;  ++y)
    {
      ++it;

        for(int  x = 0;  x < frm.w-1;  ++x)
        {
          put_pixel(*it++,frm.x+x,frm.y+y);
        }
    }


  update_because_of_image_changed();
}


void
shift_chip_right()
{
  auto  frm = selection::get_rect().to_frame();

  auto  it = copy(frm);

    for(int  y = 0;  y < frm.h;  ++y)
    {
        for(int  x = 1;  x < frm.w;  ++x)
        {
          put_pixel(*it++,frm.x+x,frm.y+y);
        }


      ++it;
    }


  update_because_of_image_changed();
}


void
shift_chip_down()
{
  auto  frm = selection::get_rect().to_frame();

  auto  it = copy(frm);

    for(int  y = 0;  y < frm.h-1;  ++y){
    for(int  x = 0;  x < frm.w  ;  ++x){
      put_pixel(*it++,frm.x+x,frm.y+y+1);
    }}


  update_because_of_image_changed();
}




void
clear_chip()
{
    for(int  y = 0;  y < get_chip_height();  ++y){
    for(int  x = 0;  x < get_chip_width() ;  ++x){
      put_pixel(0,x,y);
    }}


  update_because_of_image_changed();
}




}




