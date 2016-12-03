#include"mkqbf_widget.hpp"
#include"mkqbf_core.hpp"




using namespace oat;


namespace{
void
change_p(RadioForm::Member&  m)
{
    if(m.current)
    {
      core::change_process(m.index);
    }
}


void
change_i(Dial&  dial, int  old_value)
{
  core::change_index(dial.get_value());
}


void
clear_(Button&  btn)
{
    if(btn->test_unpressed())
    {
      core::clear_attribute_all();
    }
}


void
save(Button&  btn)
{
    if(btn->test_unpressed())
    {
      core::write();
    }
}


}




Widget*
create_manager_widget()
{
  auto      btn = new Button(new Text(u"保存"),save);
  auto  clr_btn = new Button(new Text(u"全属性をクリア"),clear_);

  auto  frm = new RadioForm({new Text(u"下位BGチップを設定"),
                             new Text(u"上位BGチップを設定"),
                             new Text(u"属性を設定")},change_p);

  auto  dia = new Dial(new Text(u"インデックス"),99,1);

  dia->set_callback(change_i);

  auto  row = new TableRow({frm,clr_btn});

  return new TableColumn({row,dia,btn});
}





