#ifndef OAT_NOTEBOOK_HPP
#define OAT_NOTEBOOK_HPP


#include"oat_container.hpp"




namespace oat{


class
NoteBook: public Container
{
protected:
  void  reform() override;

  Widget*  top;

  int  top_index;

public:
   NoteBook();


  void  change_top(int  i);

  void  join(Widget*  child, int  x, int  y);

  void  update_sizes() override;

};


}


#endif




