#include"mg_color_selection.hpp"




namespace color_selection{


namespace{


int  index;


class
PrivateWidget: public oat::Widget
{
public:
  PrivateWidget();

  void  process_mouse(const oat::Mouse&  mouse) override;
  void  render() override;

};




constexpr int   frame_size = 20;
constexpr int  square_size = 16;


PrivateWidget::
PrivateWidget()
{
  change_content_width( frame_size*element_number/2);
  change_content_height(frame_size*2);
}




void
PrivateWidget::
process_mouse(const oat::Mouse&  mouse)
{
  auto  pt = get_mouse_point(mouse);

    if(mouse.left.test_pressing())
    {
      int  v = (pt.x/frame_size)<<1;

      v |= ((pt.y < frame_size)? 0:1);


      index = v;

      need_to_redraw();
    }
}


void
PrivateWidget::
render()
{
  fill();


  auto  pt = content.point;

  const oat::Color*  color = table;

    for(int  x = 0;  x < element_number/2;  ++x)
    {
      fill_rect(*color++,pt.x+(frame_size*x),pt.y,square_size,square_size);
      fill_rect(*color++,pt.x+(frame_size*x),pt.y+frame_size,square_size,square_size);
    }


  auto  v = index;

  draw_rect(oat::const_color::white,pt.x+(frame_size*(v>>1)),
                                    pt.y+(v&1? frame_size:0),frame_size,frame_size);
}


}



void
change_index(int  v)
{
  index = v;
}


int
get_index()
{
  return index;
}


oat::Widget*
create_widget()
{
  return new PrivateWidget;
}




}





