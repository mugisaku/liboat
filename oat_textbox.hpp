#ifndef OAT_TEXTBOX_HPP
#define OAT_TEXTBOX_HPP


#include"oat_widget.hpp"
#include<string>


namespace oat{


class
TextBox: public Widget
{
protected:
  int  column_number;

  using RowList = std::list<std::u16string>;

  RowList  row_list;

  RowList::iterator  current;

public:
  TextBox(int  col_n, int  row_n);

  void  change_string(std::u16string&&  s);

  void  render() override;
  
};


}




#endif




