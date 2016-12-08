#include"mg_board.hpp"
#include"mg_image.hpp"
#include"mg_area_selection.hpp"
#include"mg_color_selection.hpp"
#include"mg_message.hpp"




namespace board{


using namespace oat;


namespace{


std::vector<Square>::const_iterator
copy(const Frame&  frm)
{
  static std::vector<Square>  buffer;

  buffer.clear();
  
    for(int  y = 0;  y < frm.h;  ++y){
    for(int  x = 0;  x < frm.w;  ++x){
      buffer.emplace_back(get_square(frm.x+x,frm.y+y));
    }}


  return buffer.cbegin();
}




void
shift_chip_up(Button&  btn)
{
    if(btn->test_unpressed())
    {
      auto  frm = area_selection::get_rect().to_frame();

      auto  it = copy(frm);

      it += frm.w;

        for(int  y = 0;  y < frm.h-1;  ++y){
        for(int  x = 0;  x < frm.w  ;  ++x){
          put_square(*it++,frm.x+x,frm.y+y);
        }}


      message::set_flag(message::image_modified_flag);
    }
}


void
shift_chip_left(Button&  btn)
{
    if(btn->test_unpressed())
    {
      auto  frm = area_selection::get_rect().to_frame();

      auto  it = copy(frm);

        for(int  y = 0;  y < frm.h;  ++y)
        {
          ++it;

            for(int  x = 0;  x < frm.w-1;  ++x)
            {
              put_square(*it++,frm.x+x,frm.y+y);
            }
        }


      message::set_flag(message::image_modified_flag);
    }
}


void
shift_chip_right(Button&  btn)
{
    if(btn->test_unpressed())
    {
      auto  frm = area_selection::get_rect().to_frame();

      auto  it = copy(frm);

        for(int  y = 0;  y < frm.h;  ++y)
        {
            for(int  x = 1;  x < frm.w;  ++x)
            {
              put_square(*it++,frm.x+x,frm.y+y);
            }


          ++it;
        }


      message::set_flag(message::image_modified_flag);
    }
}


void
shift_chip_down(Button&  btn)
{
    if(btn->test_unpressed())
    {
      auto  frm = area_selection::get_rect().to_frame();

      auto  it = copy(frm);

        for(int  y = 0;  y < frm.h-1;  ++y){
        for(int  x = 0;  x < frm.w  ;  ++x){
          put_square(*it++,frm.x+x,frm.y+y+1);
        }}


      message::set_flag(message::image_modified_flag);
    }
}




}



oat::Widget*
create_operate_widget()
{
  using namespace oat;


  auto  shu_btn = new Button(new Text(u"上へ"),shift_chip_up);
  auto  shl_btn = new Button(new Text(u"左へ"),shift_chip_left);
  auto  shr_btn = new Button(new Text(u"右へ"),shift_chip_right);
  auto  shd_btn = new Button(new Text(u"下へ"),shift_chip_down);

  return new TableRow({new Text(u"シフト"),shu_btn,shl_btn,shr_btn,shd_btn});
}


}



