#include"gramk_album.hpp"
#include<cstring>




Album::
Album(Callback  cb):
callback(cb)
{
  table.resize(table_width*table_height);

    for(auto&  ptr: table)
    {
      ptr = new SuperCard;
    }


  callback(table[0]);

  change_content_width( Card::fixed_width *table_width);
  change_content_height(Card::fixed_height*table_height);

  style.background_color = oat::const_color::blue;
}




void
Album::
process_mouse(const oat::Mouse&  mouse)
{
  auto  pt = get_mouse_point(mouse);

    if(mouse.left.test_pressed())
    {
      cursor.x = pt.x/Card::fixed_width;
      cursor.y = pt.y/Card::fixed_height;

      callback(table[(table_width*cursor.y)+cursor.x]);

      need_to_redraw();
    }
}




void
Album::
render()
{
  fill();

  auto  pt = content.point;

    for(int  y = 0;  y < table_height;  ++y){
    for(int  x = 0;  x <  table_width;  ++x){
      auto&  c = *table[(table_width*y)+x];

      c.draw(*this,pt.x+(Card::fixed_width*x),
                   pt.y+(Card::fixed_height*y));
    }}


  draw_rect(oat::const_color::red,pt.x+(Card::fixed_width *cursor.x),
                                  pt.y+(Card::fixed_height*cursor.y),Card::fixed_width,Card::fixed_height);
}


const SuperCard*
Album::
get_current() const
{
  return table[(table_width*cursor.y)+cursor.x];
}





