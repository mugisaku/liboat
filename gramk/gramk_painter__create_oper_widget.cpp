#include"gramk_painter.hpp"




using namespace oat;


namespace{




void
undo(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.get_target()->undo();

      p.need_to_redraw();
    }
}


void
clear_selection(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.clear_selection();

      p.need_to_redraw();
    }
}


void
copy(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.copy();
    }
}


void
clear_image(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.clear_image();

      p.need_to_redraw();
    }
}


void
revolve(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.get_target()->revolve(p.get_selecting_rect());

      p.need_to_redraw();
    }
}


void
reverse_horizontally(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.get_target()->reverse_horizontally(p.get_selecting_rect());

      p.need_to_redraw();
    }
}


void
reverse_vertically(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.get_target()->reverse_vertically(p.get_selecting_rect());

      p.need_to_redraw();
    }
}


void
mirror_vertically(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.get_target()->mirror_vertically(p.get_selecting_rect());

      p.need_to_redraw();
    }
}




void
shift_up(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.get_target()->shift_up(p.get_selecting_rect());

      p.need_to_redraw();
    }
}


void
shift_left(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.get_target()->shift_left(p.get_selecting_rect());

      p.need_to_redraw();
    }
}


void
shift_right(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.get_target()->shift_right(p.get_selecting_rect());

      p.need_to_redraw();
    }
}


void
shift_down(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.get_target()->shift_down(p.get_selecting_rect());

      p.need_to_redraw();
    }
}




void
rotate_up(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.get_target()->shift_up(p.get_selecting_rect(),true);

      p.need_to_redraw();
    }
}


void
rotate_left(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.get_target()->shift_left(p.get_selecting_rect(),true);

      p.need_to_redraw();
    }
}


void
rotate_right(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.get_target()->shift_right(p.get_selecting_rect(),true);

      p.need_to_redraw();
    }
}


void
rotate_down(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.get_target()->shift_down(p.get_selecting_rect(),true);

      p.need_to_redraw();
    }
}




void
change_base(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

    if(btn->test_unpressed())
    {
      p.change_base();
    }
}




void
hide_base(Button&  btn)
{
  auto&  p = *static_cast<Painter*>(btn.get_userdata());

  p.change_hide_base_flag(btn->test_pressing());
}


}




oat::Widget*
Painter::
create_oper_widget()
{
  auto  und_btn = new Button(new Text(u"アンドゥ"),undo);
  auto  cpy_btn = new Button(new Text(u"コピー"),::copy);
  auto  rse_btn = new Button(new Text(u"選択解除"),::clear_selection);
  auto  clr_btn = new Button(new Text(u"クリア"),::clear_image);

  auto  rvl_btn = new Button(new Text(u"右回転"),revolve);
  auto  rvh_btn = new Button(new Text(u"水平反転"),reverse_horizontally);
  auto  rvv_btn = new Button(new Text(u"垂直反転"),reverse_vertically);
  auto  mrv_btn = new Button(new Text(u"垂直鏡像"),mirror_vertically);


  auto  shu_btn = new Button(new Text(u"上へ"),shift_up);
  auto  shl_btn = new Button(new Text(u"左へ"),shift_left);
  auto  shr_btn = new Button(new Text(u"右へ"),shift_right);
  auto  shd_btn = new Button(new Text(u"下へ"),shift_down);

  auto  rou_btn = new Button(new Text(u"上へ"),rotate_up);
  auto  rol_btn = new Button(new Text(u"左へ"),rotate_left);
  auto  ror_btn = new Button(new Text(u"右へ"),rotate_right);
  auto  rod_btn = new Button(new Text(u"下へ"),rotate_down);


  auto  chb_btn = new Button(new Text(u"下敷きに使う"),::change_base);
  auto  hib_btn = new Button(new Text(u"下敷きを隠す"),hide_base);


  und_btn->set_userdata(this);
  cpy_btn->set_userdata(this);
  rse_btn->set_userdata(this);
  clr_btn->set_userdata(this);
  rvl_btn->set_userdata(this);
  rvh_btn->set_userdata(this);
  rvv_btn->set_userdata(this);
  mrv_btn->set_userdata(this);
  shu_btn->set_userdata(this);
  shl_btn->set_userdata(this);
  shr_btn->set_userdata(this);
  shd_btn->set_userdata(this);
  rou_btn->set_userdata(this);
  rol_btn->set_userdata(this);
  ror_btn->set_userdata(this);
  rod_btn->set_userdata(this);
  chb_btn->set_userdata(this);
  hib_btn->set_userdata(this);

  hib_btn->get_module().use_toggle();

  auto   b_col = new TableColumn({chb_btn,hib_btn});
  auto  sr_col = new TableColumn({new TableRow({new Text(u"シフト"),shu_btn,shl_btn,shr_btn,shd_btn}),
                                  new TableRow({new Text(u"ローテ"),rou_btn,rol_btn,ror_btn,rod_btn})});

  return new TableColumn({new TableRow({und_btn,cpy_btn,rse_btn,clr_btn}),
                          new TableRow({rvl_btn,rvh_btn,rvv_btn,mrv_btn}),
                          new TableRow({sr_col,b_col}),
                        });
}




