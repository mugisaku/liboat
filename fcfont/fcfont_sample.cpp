#include"fcfont_sample.hpp"
#include"fcfont_combinedselector.hpp"


using namespace oat;


namespace fcfont{


namespace{


const char16_t*
string = 
u"0123456789!?abcdefghijklmnopqrstuvwxyz"
u"ABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/=!\"#$%&\'()~|{}[]:;_"
u"ぁあぃいぅうぇえぉおかがきぎくぐけげこごさざしじすずせぜそぞただちぢっつづてでとどなにぬねの"
u"はばぱひびぴふぶぷへべぺほぼぽまみむめもゃやゅゆょよらりるれろわをんー"
u"ァアィイゥウェエォオカガキギクグケゲコゴサザシジスズセゼソゾタダチヂッツヅテデトドナニヌネノ"
u"ハバパヒビピフブプヘベペホボポマミムメモャヤュユョヨラリルレロワヲン";


constexpr int  x_element_number = 60;
constexpr int  y_element_number =  8;


}




Sample::
Sample()
{
  style.background_color = const_color::black;

  change_content_width(  8*x_element_number);
  change_content_height(16*y_element_number);
}




void
Sample::
render()
{
  auto  pt = content.point;

  fill();

  int  x = 0;
  int  y = 0;

  const char16_t*  p = string;

    while(*p)
    {
        if((x+8) >= content.width)
        {
          x  =  0;
          y += 16;
        }


        if((y+16) >= content.height)
        {
          break;
        }


      auto  c = Combined::pointer_table[*p++];

        if(c)
        {
          CombinedSelector::draw_combined(*c,this,pt.x+x,pt.y+y);
        }


      x += 8;
    }
}




}



