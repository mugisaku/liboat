#include"gramk_album.hpp"
#include<cstring>




namespace{


void
inscol(oat::Button&  btn)
{
    if(btn->test_pressed())
    {
      static_cast<Album*>(btn.get_userdata())->insert_column();
    }
}


void
remcol(oat::Button&  btn)
{
    if(btn->test_pressed())
    {
      static_cast<Album*>(btn.get_userdata())->remove_column();
    }
}


void
insrow(oat::Button&  btn)
{
    if(btn->test_pressed())
    {
      static_cast<Album*>(btn.get_userdata())->insert_row();
    }
}


void
remrow(oat::Button&  btn)
{
    if(btn->test_pressed())
    {
      static_cast<Album*>(btn.get_userdata())->remove_row();
    }
}


}




oat::Widget*
Album::
create_operator_widget()
{
  auto  inscol_btn = new oat::Button(new oat::Text(u"行挿入"),inscol);
  auto  remcol_btn = new oat::Button(new oat::Text(u"行削除"),remcol);
  auto  insrow_btn = new oat::Button(new oat::Text(u"列挿入"),insrow);
  auto  remrow_btn = new oat::Button(new oat::Text(u"列削除"),remrow);

  inscol_btn->set_userdata(this);
  remcol_btn->set_userdata(this);
  insrow_btn->set_userdata(this);
  remrow_btn->set_userdata(this);

  auto  coltbl = new oat::TableRow({inscol_btn,remcol_btn});
  auto  rowtbl = new oat::TableRow({insrow_btn,remrow_btn});

  return new oat::TableColumn({coltbl,rowtbl});
}




