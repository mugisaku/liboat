#include"mg_board.hpp"
#include"mg_image.hpp"
#include"mg_area_selection.hpp"
#include"mg_color_selection.hpp"




namespace board{


using namespace oat;


namespace{


using Table = Square[table_size][table_size];


Table  table;


int  process;
int  index;


void
change_p(oat::RadioForm::Member&  m)
{
    if(m.current)
    {
      process = m.index;
    }
}


void
change_i(oat::Dial&  dial, int  old_value)
{
  static const char16_t*  const table[] =
  {
    u"NULL",
    u"平地",
    u"荒地",
    u"沼地",
    u"砂地",
    u"雪原",
    u"氷原",
    u"草原",
    u"川",
    u"森",
    u"山",
    u"海",
  };

  auto&  txt = *static_cast<Text*>(dial.get_userdata());

  index = dial.get_value();

  txt.change_string((index < 12) ?table[index]:u"----");
}


void
clear_attribute_all(oat::Button&  btn)
{
    if(btn->test_unpressed())
    {
        for(auto&  arr: table){
        for(auto&  sq: arr){
          sq.attribute = 0;
        }}
    }
}


void
clear_selection(oat::Button&  btn)
{
    if(btn->test_unpressed())
    {
      area_selection::reset(table_size,table_size);
    }
}


void
save(oat::Button&  btn)
{
    if(btn->test_unpressed())
    {
      write();
    }
}


class
PrivateWidget: public oat::Widget
{
  oat::Point  cursor;

  void  draw_selection_frame();

  void  draw_digit(int  d, const oat::Color&  color, int  x, int  y);

  void  draw_chip(const oat::Point&  chip_point, int  x_base, int  y_base);
  void  draw_attribute(int  attr, int  x_base, int  y_base);
  void  draw_bg1();
  void  draw_bg2(bool  with_attribute);
  void  draw_bg3();

public:
  PrivateWidget();

  void  process_mouse(const oat::Mouse&  mouse) override;

  void  render() override;

};



PrivateWidget::
PrivateWidget()
{
  change_content_width( image::get_chip_width() *table_size);
  change_content_height(image::get_chip_height()*table_size);

  style.background_color = oat::const_color::green;
}




void
PrivateWidget::
process_mouse(const oat::Mouse&  mouse)
{
  cursor = get_mouse_point(mouse);

  cursor.x /= image::get_chip_width();
  cursor.y /= image::get_chip_height();

  auto&  frm = image::get_frame();

  auto&  sq = table[cursor.y][cursor.x];

    switch(process)
    {
  case(Process::arrange_lower_chip): if(mouse.left.test_pressing()){sq.lower = oat::Point(frm.x,frm.y);}break;
  case(Process::arrange_upper_chip): if(mouse.left.test_pressing()){sq.upper = oat::Point(frm.x,frm.y);}break;
  case(Process::change_attribute  ):
           if(mouse.left.test_pressing() ){sq.attribute = noentry_flag|index;}
      else if(mouse.right.test_pressing()){sq.attribute =              index;}
      break;
  case(Process::transform_area_frame):
        if(mouse.left.test_pressed())
        {
          area_selection::grab(cursor.x,cursor.y);
        }

      else
        if(mouse.left.test_pressing())
        {
          area_selection::move(cursor.x,cursor.y);
        }
      break;
    }


  need_to_redraw();
}




void
PrivateWidget::
draw_selection_frame()
{
  auto&  pt = content.point;

  auto&  rect = area_selection::get_rect();

  const int  w = image::get_chip_width();

  auto&  color = oat::const_color::blue;

  draw_rect(color,pt.x+(w*rect.left),
                                     pt.y+(w*rect.top),
                                     (w*((rect.right-rect.left)+1)),
                                     (w*((rect.bottom-rect.top)+1)));

  draw_rect(color,pt.x+(w*rect.left),
                                     pt.y+(w*rect.top),
                                     w,
                                     w);

  draw_rect(color,pt.x+(w*rect.right),
                                     pt.y+(w*rect.top),
                                     w,
                                     w);

  draw_rect(color,pt.x+(w*rect.left),
                                     pt.y+(w*rect.bottom),
                                     w,
                                     w);

  draw_rect(color,pt.x+(w*rect.right),
                                     pt.y+(w*rect.bottom),
                                     w,
                                     w);
}


void
PrivateWidget::
draw_digit(int  d, const oat::Color&  color, int  x, int  y)
{
  using Glyph = uint8_t[8];

  constexpr Glyph  digit_glyph[] =
  {
    {0x00,0x3E,0x63,0x63,0x63,0x63,0x63,0x3E,},
    {0x00,0x0C,0x1C,0x0C,0x0C,0x0C,0x0C,0x3F,},
    {0x00,0x3E,0x63,0x07,0x0E,0x1C,0x38,0x7F,},
    {0x00,0x3E,0x63,0x03,0x1E,0x03,0x63,0x3E,},
    {0x00,0x06,0x0E,0x1E,0x36,0x66,0x7F,0x06,},
    {0x00,0x7F,0x60,0x60,0x7E,0x03,0x63,0x3E,},
    {0x00,0x3E,0x73,0x60,0x7E,0x63,0x63,0x3E,},
    {0x00,0x7F,0x03,0x06,0x0C,0x18,0x30,0x30,},
    {0x00,0x3E,0x63,0x63,0x3E,0x63,0x63,0x3E,},
    {0x00,0x3E,0x63,0x63,0x3F,0x03,0x63,0x3E,},
  };


  const uint8_t*  p = digit_glyph[d];

    for(int  yy = 0;  yy < 8;  yy += 1)
    {
      auto  c = *p++;

        for(int  xx = 0;  xx < 8;  xx += 1)
        {
            if(c&0x80)
            {
              draw_dot(color,x+xx,y+yy);
            }


          c <<= 1;
        }
    }
}


void
PrivateWidget::
draw_chip(const oat::Point&  chip_point, int  x_base, int  y_base)
{
  const int  w = image::get_chip_width();
  const int  h = image::get_chip_height();

    for(int  yy = 0;  yy < h;  yy += 1){
    for(int  xx = 0;  xx < w;  xx += 1){
      auto  v = image::get_pixel(chip_point.x+xx,
                                 chip_point.y+yy);

        if(v&8)
        {
          draw_dot(color_selection::table[v&7],x_base+xx,
                                               y_base+yy);
        }
    }}
}


void
PrivateWidget::
draw_attribute(int  attr, int  x_base, int  y_base)
{
  fill_rect(oat::const_color::white,x_base+4,
                                    y_base+12,16,8);

  auto  d = (attr&0x7F);

  auto  color = (attr&noentry_flag)? oat::const_color::red
                                   : oat::const_color::blue;

  int  d1 = d/10;

  d %= 10;

  draw_digit(d1,color,x_base+4,
                      y_base+12);

  draw_digit(d ,color,x_base+12,
                      y_base+12);
  draw_digit(d ,color,x_base+12,
                      y_base+12);
}


void
PrivateWidget::
draw_bg1()
{
  const int  w = image::get_chip_width();
  const int  h = image::get_chip_height();

  auto  pt = content.point;

    for(int  y = 0;  y < table_size;  y += 1){
    for(int  x = 0;  x < table_size;  x += 1){
      auto&  sq = get_square(x,y);

      draw_chip(sq.lower,
                pt.x+w*x,
                pt.y+h*y);
    }}
}


void
PrivateWidget::
draw_bg2(bool  with_attribute)
{
  const int  w = image::get_chip_width();
  const int  h = image::get_chip_height();

  auto  pt = content.point;

    for(int  y = 0;  y < table_size;  y += 1){
    for(int  x = 0;  x < table_size;  x += 1){
      auto&  sq = get_square(x,y);

      const int  x_base = pt.x+w*x;
      const int  y_base = pt.y+h*y;

      draw_chip(sq.lower,x_base,y_base);
      draw_chip(sq.upper,x_base,y_base);

        if(with_attribute)
        {
          draw_attribute(sq.attribute,x_base,y_base);
        }
   }}
}


void
PrivateWidget::
draw_bg3()
{
  const int  w = image::get_chip_width();
  const int  h = image::get_chip_height();

  auto  pt = content.point;

    for(int  y = 0;  y < table_size;  y += 1){
    for(int  x = 0;  x < table_size;  x += 1){
      auto&  sq = get_square(x,y);

      const int  x_base = pt.x+w*x;
      const int  y_base = pt.y+h*y;

      draw_attribute(sq.attribute,x_base,y_base);
   }}
}


void
PrivateWidget::
render()
{
  fill();

  auto  pt = content.point;

    switch(process)
    {
  case(Process::arrange_lower_chip):
      draw_bg1();
      break;
  case(Process::arrange_upper_chip):
      draw_bg2(false); 
      break;
  case(Process::change_attribute):
      draw_bg2(true); 
      break;
  case(Process::transform_area_frame):
      draw_bg1();
      draw_selection_frame();
      return;
      break;
    }


    if(area_selection::test_whether_transformed())
    {
      draw_selection_frame();
    }


  const int  w = image::get_chip_width();
  const int  h = image::get_chip_height();

  draw_rect(oat::const_color::red,pt.x+(w*cursor.x),
                                  pt.y+(h*cursor.y),
                                  w,
                                  h);
}


oat::TextBox*
textbox;


}




void
change_path_text(std::u16string&&  s)
{
  textbox->change_string(std::move(s));
}


const Square&
get_square(int  x, int  y)
{
  return table[y][x];
}


void
put_square(const Square&  sq, int  x, int  y)
{
  table[y][x] = sq;
}


oat::Widget*  create_operate_widget();


oat::Widget*
create_widget()
{
  auto  main = new PrivateWidget;

  textbox = new oat::TextBox(16,1);

  textbox->change_string(u"__new.qbf");

  auto      btn = new Button(new Text(u"保存"),save);
  auto  clratt_btn = new Button(new Text(u"全属性をクリア"),clear_attribute_all);
  auto  clrsel_btn = new Button(new Text(u"選択をクリア"),clear_selection);

  auto  opw = create_operate_widget();

  auto  frm = new RadioForm({new Text(u"下位BGチップを設定"),
                             new Text(u"上位BGチップを設定"),
                             new Text(u"属性を設定"),
                             new Text(u"エリアを選択")},change_p);


  auto  id_txt = new Text(u"NULL");

  auto  dia = new Dial(new Text(u"インデックス"),99,1);

  

  dia->set_callback(change_i);
  dia->set_userdata(id_txt);

  auto  save_module = new oat::TableRow({textbox,btn});

  auto  rcol = new TableColumn({frm,clratt_btn,clrsel_btn});

  auto  top_row = new TableRow({main,rcol});

  return new TableColumn({top_row,new TableRow({dia,id_txt}),opw,save_module});
}


}



