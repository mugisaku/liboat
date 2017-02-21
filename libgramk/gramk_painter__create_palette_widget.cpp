#include"gramk_painter.hpp"




namespace{


class
PrivateWidget: public oat::Widget
{
  Painter&  p;

public:
  PrivateWidget(Painter&  p_);

  void  process_mouse(const oat::Mouse&  mouse) override;
  void  render() override;

};




constexpr int   frame_size = 20;
constexpr int  square_size = 16;


PrivateWidget::
PrivateWidget(Painter&  p_):
p(p_)
{
  change_content_width( frame_size*number_of_colors/2);
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


      p.change_current_color(v);

      p.need_to_redraw();

      need_to_redraw();
    }
}


void
PrivateWidget::
render()
{
  fill();


  auto  pt = content.point;

  const oat::Color*  color = palette;

    for(int  x = 0;  x < number_of_colors/2;  ++x)
    {
      fill_rect(*color++,pt.x+(frame_size*x),pt.y,square_size,square_size);
      fill_rect(*color++,pt.x+(frame_size*x),pt.y+frame_size,square_size,square_size);
    }


  auto  v = p.get_current_color();

  draw_rect(oat::const_color::white,pt.x+(frame_size*(v>>1)),
                                    pt.y+(v&1? frame_size:0),frame_size,frame_size);
}


}



oat::Widget*
Painter::
create_palette_widget()
{
  return new PrivateWidget(*this);
}





