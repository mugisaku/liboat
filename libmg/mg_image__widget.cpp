#include"mg_image.hpp"
#include"mg_color_selection.hpp"




namespace image{


namespace{


class
PrivateWidget: public oat::Widget
{
  oat::Point  cursor;

public:
  PrivateWidget();

  void  process_mouse(const oat::Mouse&  mouse) override;

  void  render() override;

};


PrivateWidget::
PrivateWidget()
{
  change_content_width( size);
  change_content_height(size);

  style.background_color = oat::const_color::blue;
}




void
PrivateWidget::
process_mouse(const oat::Mouse&  mouse)
{
  cursor = get_mouse_point(mouse);

  auto&  frm = get_frame();

    if((cursor.x+frm.w) >= size)
    {
      cursor.x = size-frm.w;
    }

  else
    {
      cursor.x /= frm.w;
      cursor.x *= frm.w;
    }


    if((cursor.y+frm.h) >= size)
    {
      cursor.y = size-frm.h;
    }

  else
    {
      cursor.y /= frm.h;
      cursor.y *= frm.h;
    }


    if(mouse.left.test_pressing())
    {
      change_frame_point(cursor);
    }


  cursor.x /= frm.w;
  cursor.y /= frm.h;

  need_to_redraw();
}




void
PrivateWidget::
render()
{
  fill();

  auto  pt = content.point;

    for(int  y = 0;  y < size;  y += 1){
    for(int  x = 0;  x < size;  x += 1){
      auto  v = get_pixel(x,y);

        if(v&8)
        {
          draw_dot(color_selection::table[v&7],pt.x+x,
                                               pt.y+y);
        }
    }}


  auto&  frm = get_frame();

  draw_rect(oat::const_color::red,pt.x+(frm.w*cursor.x),
                                  pt.y+(frm.h*cursor.y),
                                  frm.w,
                                  frm.h);

  draw_rect(oat::const_color::green,pt.x+frm.x,
                                    pt.y+frm.y,
                                    frm.w,
                                    frm.h);

  draw_rect(oat::const_color::yellow,pt.x+frm.x+1,
                                     pt.y+frm.y+1,
                                     frm.w-2,
                                     frm.h-2);
}


void
save(oat::Button&  btn)
{
    if(btn->test_unpressed())
    {
      write();
    }
}


oat::TextBox*
textbox;


}


void
change_path_text(std::u16string&&  s)
{
  textbox->change_string(std::move(s));
}



oat::Widget*
create_main_widget()
{
  auto  main = new PrivateWidget;

  auto   btn = new oat::Button(new oat::Text(u"PNGで保存"),save);

  textbox = new oat::TextBox(16,1);

  textbox->change_string(u"__new.png");

  auto  save_module = new oat::TableRow({textbox,btn});

  return new oat::TableColumn({main,save_module});
}




}




