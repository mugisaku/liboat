#include"gramk_painter.hpp"




namespace{


void
change(oat::CheckForm&  form, oat::CheckForm::Member&  m)
{
  auto&  p = *static_cast<Painter*>(form.get_userdata());

    if(m.current)
    {
      p.change_mode(static_cast<PaintingMode>(m.index));
    }
}


}


oat::Widget*
Painter::
create_mode_widget()
{
  auto  frm = new oat::RadioForm({new oat::Text(u"点を打つ"),
                                  new oat::Text(u"線を引く"),
                                  new oat::Text(u"楕円を引く"),
                                  new oat::Text(u"矩形を引く"),
                                  new oat::Text(u"矩形を塗る"),
                                  new oat::Text(u"領域を塗りつぶす"),
                                  new oat::Text(u"領域を選択する"),
                                  new oat::Text(u"貼り付け"),
                                  new oat::Text(u"重ね貼り"),
                                  });
 
  frm->set_callback(&change);
  frm->set_userdata(this);

  return frm;
}




