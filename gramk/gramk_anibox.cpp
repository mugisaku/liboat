#include"gramk_anibox.hpp"
#



constexpr int  pixel_size = 4;




AniBox::
AniBox(GetCard  cb):
callback(cb),
current(0),
character('0'),
last_time(0),
interval_time(200)
{
  change_content_width( Card::width *pixel_size                  );
  change_content_height(Card::height*pixel_size+oat::font::height);
}




void
AniBox::
speed_up()
{
  interval_time >>= 1;
}


void
AniBox::
speed_down()
{
  interval_time <<= 1;
  interval_time  |= 1;
}


void
AniBox::
push()
{
    if(list.size() < 9)
    {
      list.emplace_back(callback());

      ++character;
    }
}


void
AniBox::
pop()
{
    if(list.size())
    {
      list.pop_back();

      --character;

      current = 0;
    }
}


void
AniBox::
clear()
{
  list.clear();

  character = '0';

  current = 0;
}




void
AniBox::
check(uint32_t  now)
{
    if(list.size())
    {
        if(now >= (last_time+interval_time))
        {
          last_time = now;

            if(++current >= list.size())
            {
              current = 0;
            }


          need_to_redraw();
        }
    }
}


void
AniBox::
render()
{
  fill();

  auto  pt = content.point;

    if(list.size())
    {
      list[current]->render(Card::width,Card::height,*this,pt.x,pt.y,pixel_size);
    }


  draw_unicode(oat::const_color::white,character,pt.x,pt.y+(pixel_size*Card::height));
}




namespace{
void
spu_cb(oat::Button&  btn)
{
    if(btn->test_pressed())
    {
      static_cast<AniBox*>(btn.get_userdata())->speed_up();
    }
}


void
spd_cb(oat::Button&  btn)
{
    if(btn->test_pressed())
    {
      static_cast<AniBox*>(btn.get_userdata())->speed_down();
    }
}


void
push_cb(oat::Button&  btn)
{
    if(btn->test_pressed())
    {
      static_cast<AniBox*>(btn.get_userdata())->push();
    }
}


void
pop_cb(oat::Button&  btn)
{
    if(btn->test_pressed())
    {
      static_cast<AniBox*>(btn.get_userdata())->pop();
    }
}


void
clear_cb(oat::Button&  btn)
{
    if(btn->test_pressed())
    {
      static_cast<AniBox*>(btn.get_userdata())->clear();
    }
}


}


oat::Widget*
AniBox::
create_ctrl_widget()
{
  auto  psh_btn = new oat::Button(new oat::Text(u"push"),push_cb);
  auto  pop_btn = new oat::Button(new oat::Text(u"pop"),pop_cb);
  auto  clr_btn = new oat::Button(new oat::Text(u"クリア"),clear_cb);
  auto  spu_btn = new oat::Button(new oat::Text(u"速く"),spu_cb);
  auto  spd_btn = new oat::Button(new oat::Text(u"遅く"),spd_cb);

  spu_btn->set_userdata(this);
  spd_btn->set_userdata(this);
  psh_btn->set_userdata(this);
  pop_btn->set_userdata(this);
  clr_btn->set_userdata(this);

  return new oat::TableColumn({psh_btn,pop_btn,clr_btn,spu_btn,spd_btn});
}





