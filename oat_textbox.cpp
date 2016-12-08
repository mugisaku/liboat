#include"oat_textbox.hpp"
#include"oat_font.hpp"




namespace oat{




TextBox::
TextBox(int  col_n, int  row_n):
column_number(col_n),
row_list(row_n)
{
  change_content_width(  font::width*col_n);
  change_content_height(font::height*row_n);

  current = row_list.begin();
}




void
TextBox::
change_string(std::u16string&&  s)
{
  *current = std::move(s);

  need_to_redraw();
}


void
TextBox::
render()
{
  auto  pt = content.point;

  fill();

    for(auto&  row: row_list)
    {
      int  pos = 0;

        for(auto  c: row)
        {
            if(pos >= column_number)
            {
              break;
            }


          draw_unicode(style.font_color,c,pt.x+(font::width*pos++),pt.y);
        }


      pt.y += font::height;
    }
}


}




