#include"gramk_anibox.hpp"
#



constexpr int  pixel_size = 2;




AniBox::
AniBox(GetCard  cb):
callback(cb),
current(0),
last_time(0),
interval_time(200)
{
  change_content_width( Card::fixed_width *pixel_size);
  change_content_height(Card::fixed_height*pixel_size);
}




void
AniBox::
push()
{
  list.emplace_back(callback());
}


void
AniBox::
pop()
{
    if(list.size())
    {
      list.pop_back();

      current = 0;
    }
}


void
AniBox::
clear()
{
  list.clear();

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
      list[current]->draw(*this,pt.x,pt.y);
    }
}




namespace{
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
  auto  clr_btn = new oat::Button(new oat::Text(u"clear"),clear_cb);

  psh_btn->set_userdata(this);
  pop_btn->set_userdata(this);
  clr_btn->set_userdata(this);

  return new oat::TableColumn({psh_btn,pop_btn,clr_btn});
}





