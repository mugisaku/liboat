#include"mg_image.hpp"
#include"mg_message.hpp"
#include"mg_area_selection.hpp"
#include<cstring>




namespace image{




namespace{


using namespace oat;


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




bool
table[80][80];


void
search(int  color_index_, int  target, int  x, int  y)
{
  auto&  e = table[y][x];

    if(!e)
    {
      e = true;

        if(get_chip_pixel(x,y) == target)
        {
          put_pixel(color_index_,x,y,true);

            if(x                        ){search(color_index_,target,x-1,y  );}
            if(y                        ){search(color_index_,target,x  ,y-1);}
            if(x < (get_chip_width() -1)){search(color_index_,target,x+1,y  );}
            if(y < (get_chip_height()-1)){search(color_index_,target,x  ,y+1);}
        }
    }
}




void
copy_chip(oat::Button&  btn)
{
    if(btn->test_unpressed())
    {
      copy_frame = area_selection::get_rect().to_frame();

      copy_buffer.clear();

        for(int  y = 0;  y < copy_frame.h;  ++y){
        for(int  x = 0;  x < copy_frame.w;  ++x){
          copy_buffer.emplace_back(get_chip_pixel(copy_frame.x+x,copy_frame.y+y));
        }}
    }
}


void
reverse_chip_horizontally(Button&  btn)
{
    if(btn->test_unpressed())
    {
      begin_to_record_string();

      auto  frm = area_selection::get_rect().to_frame();

      auto  it = copy(frm);

        for(int  y = frm.h-1;  y >=    0;  --y){
        for(int  x =       0;  x < frm.w;  ++x){
          put_pixel(*it++,frm.x+x,frm.y+y,true);
        }}


      end_to_record_string();

      message::set_flag(message::image_modified_flag);
    }
}


void
reverse_chip_vertically(Button&  btn)
{
    if(btn->test_unpressed())
    {
      begin_to_record_string();

      auto  frm = area_selection::get_rect().to_frame();

      auto  it = copy(frm);

        for(int  y =       0;  y < frm.h;  ++y){
        for(int  x = frm.w-1;  x >=    0;  --x){
          put_pixel(*it++,frm.x+x,frm.y+y,true);
        }}


      message::set_flag(message::image_modified_flag);
    }
}


void
mirror_chip_vertically(Button&  btn)
{
    if(btn->test_unpressed())
    {
      begin_to_record_string();

      auto  frm = area_selection::get_rect().to_frame();

        for(int  y = 0;  y < frm.h;  ++y)
        {
            for(int  x = 0;  x < frm.w/2;  ++x)
            {
              auto  v = get_chip_pixel(frm.x+x,frm.y+y);

              put_pixel(v,frm.x+frm.w-1-x,frm.y+y,true);
            }
        }


      end_to_record_string();

      message::set_flag(message::image_modified_flag);
    }
}




void
shift_chip_up(Button&  btn)
{
    if(btn->test_unpressed())
    {
      begin_to_record_string();

      auto  frm = area_selection::get_rect().to_frame();

      auto  it = copy(frm);

      it += frm.w;

        for(int  y = 0;  y < frm.h-1;  ++y){
        for(int  x = 0;  x < frm.w  ;  ++x){
          put_pixel(*it++,frm.x+x,frm.y+y,true);
        }}


      end_to_record_string();

      message::set_flag(message::image_modified_flag);
    }
}


void
shift_chip_left(Button&  btn)
{
    if(btn->test_unpressed())
    {
      begin_to_record_string();

      auto  frm = area_selection::get_rect().to_frame();

      auto  it = copy(frm);

        for(int  y = 0;  y < frm.h;  ++y)
        {
          ++it;

            for(int  x = 0;  x < frm.w-1;  ++x)
            {
              put_pixel(*it++,frm.x+x,frm.y+y,true);
            }
        }


      end_to_record_string();

      message::set_flag(message::image_modified_flag);
    }
}


void
shift_chip_right(Button&  btn)
{
    if(btn->test_unpressed())
    {
      begin_to_record_string();

      auto  frm = area_selection::get_rect().to_frame();

      auto  it = copy(frm);

        for(int  y = 0;  y < frm.h;  ++y)
        {
            for(int  x = 1;  x < frm.w;  ++x)
            {
              put_pixel(*it++,frm.x+x,frm.y+y,true);
            }


          ++it;
        }


      end_to_record_string();

      message::set_flag(message::image_modified_flag);
    }
}


void
shift_chip_down(Button&  btn)
{
    if(btn->test_unpressed())
    {
      begin_to_record_string();

      auto  frm = area_selection::get_rect().to_frame();

      auto  it = copy(frm);

        for(int  y = 0;  y < frm.h-1;  ++y){
        for(int  x = 0;  x < frm.w  ;  ++x){
          put_pixel(*it++,frm.x+x,frm.y+y+1,true);
        }}


      end_to_record_string();

      message::set_flag(message::image_modified_flag);
    }
}




void
clear_chip(Button&  btn)
{
    if(btn->test_unpressed())
    {
      begin_to_record_string();

        for(int  y = 0;  y < get_chip_height();  ++y){
        for(int  x = 0;  x < get_chip_width() ;  ++x){
          put_pixel(0,x,y,true);
        }}


      end_to_record_string();

      message::set_flag(message::image_modified_flag);
    }
}


void
reset_selection(Button&  btn)
{
    if(btn->test_unpressed())
    {
      area_selection::reset(get_chip_width(),get_chip_height());

      message::set_flag(message::image_modified_flag);
    }
}


}




oat::Widget*
create_edit_widget()
{
  using namespace oat;


  auto  cpy_btn = new Button(new Text(u"コピー"),copy_chip);
  auto  rse_btn = new Button(new Text(u"選択解除"),reset_selection);
  auto  clr_btn = new Button(new Text(u"クリア"),clear_chip);

  auto  rvh_btn = new Button(new Text(u"水平反転"),reverse_chip_horizontally);
  auto  rvv_btn = new Button(new Text(u"垂直反転"),reverse_chip_vertically);
  auto  mrv_btn = new Button(new Text(u"垂直鏡像"),mirror_chip_vertically);


  auto  shu_btn = new Button(new Text(u"上へ"),shift_chip_up);
  auto  shl_btn = new Button(new Text(u"左へ"),shift_chip_left);
  auto  shr_btn = new Button(new Text(u"右へ"),shift_chip_right);
  auto  shd_btn = new Button(new Text(u"下へ"),shift_chip_down);

  return new TableColumn({new TableRow({cpy_btn,rse_btn,clr_btn}),
                          new TableRow({rvh_btn,rvv_btn,mrv_btn}),
                          new TableRow({new Text(u"シフト"),shu_btn,shl_btn,shr_btn,shd_btn}),
                        });
}




void
fill_area(int  color_index_, int  x, int  y)
{
  auto  target = get_chip_pixel(x,y);

    if(target != color_index_)
    {
      begin_to_record_string();

      std::memset(&table,0,sizeof(table));

      search(color_index_,target,x,y);

      end_to_record_string();

      message::set_flag(message::image_modified_flag);
    }
}




void
paste_chip(int  x, int  y, bool  overwrite)
{
    if(copy_buffer.size())
    {
      begin_to_record_string();

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
                  put_pixel(v,x+xx,y+yy,true);
                }
            }
        }


      end_to_record_string();

      message::set_flag(message::image_modified_flag);
    }
}




}




