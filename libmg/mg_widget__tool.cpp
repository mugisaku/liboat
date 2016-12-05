#include"mg_widget.hpp"
#include"mg_core.hpp"



using namespace oat;


namespace{
void
change_tool(RadioForm::Member&  m)
{
    if(m.current)
    {
      core::change_tool_index(m.index);
    }
}
}


oat::Widget*
create_tool_widget()
{
  auto  frm = new RadioForm({new Text(u"点を打つ"),
                             new Text(u"領域を塗りつぶす"),
                             new Text(u"領域を選択する"),
                             new Text(u"貼り付け"),
                             new Text(u"重ね貼り"),
                             });
 
  frm->set_callback(change_tool);

  return frm;
}




