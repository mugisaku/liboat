#include"mg_tool_selection.hpp"




namespace tool_selection{


namespace{


int  index;


void
change(oat::RadioForm::Member&  m)
{
    if(m.current)
    {
      index = m.index;
    }
}


}


int
get_index()
{
  return index;
}


oat::Widget*
create_widget()
{
  auto  frm = new oat::RadioForm({new oat::Text(u"点を打つ"),
                                  new oat::Text(u"領域を塗りつぶす"),
                                  new oat::Text(u"領域を選択する"),
                                  new oat::Text(u"貼り付け"),
                                  new oat::Text(u"重ね貼り"),
                                  });
 
  frm->set_callback(change);

  return frm;
}


}




