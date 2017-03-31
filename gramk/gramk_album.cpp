#include"gramk_album.hpp"
#include<cstring>




int  Album::table_width ;
int  Album::table_height;


void
Album::
reset_size(int  w, int  h)
{
  table_width  = w;
  table_height = h;
}




Album::
Album(Callback  cb):
callback(cb)
{
  table.resize(table_width*table_height);

    for(auto&  ptr: table)
    {
      ptr = new Card(true);
    }


  callback(table[0]);

  change_content_width( Card::width *table_width);
  change_content_height(Card::height*table_height);

  style.background_color = oat::const_color::blue;
}




void
Album::
process_mouse(const oat::Mouse&  mouse)
{
  auto  pt = get_mouse_point(mouse);

    if(mouse.left.test_pressed())
    {
      cursor.x = pt.x/Card::width;
      cursor.y = pt.y/Card::height;

      callback(table[(table_width*cursor.y)+cursor.x]);

      need_to_redraw();
    }
}


Card&
Album::
get_card(int  x, int  y) const
{
  return *table[(table_width*y)+x];
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

      c.render(Card::width,Card::height,*this,pt.x+(Card::width *x),
                                              pt.y+(Card::height*y));
    }}


  draw_rect(oat::const_color::red,pt.x+(Card::width *cursor.x),
                                  pt.y+(Card::height*cursor.y),Card::width,Card::height);
}


const Card*
Album::
get_current() const
{
  return table[(table_width*cursor.y)+cursor.x];
}




void
Album::
insert_column()
{
    for(int  y =             0;  y < table_height;  ++y){
    for(int  x = table_width-1;  x >     cursor.x;  --x){
      get_card(x,y) = get_card(x-1,y);
    }}
}


void
Album::
remove_column()
{
    for(int  y =        0;  y < table_height ;  ++y){
    for(int  x = cursor.x;  x < table_width-1;  ++x){
      get_card(x,y) = get_card(x+1,y);
    }}
}


void
Album::
insert_row()
{
    for(int  x =              0;  x < table_width;  ++x){
    for(int  y = table_height-1;  y >    cursor.y;  --y){
      get_card(x,y) = get_card(x,y-1);
    }}
}


void
Album::
remove_row()
{
    for(int  x =        0;  x < table_width   ;  ++x){
    for(int  y = cursor.y;  y < table_height-1;  ++y){
      get_card(x,y) = get_card(x,y+1);
    }}
}




