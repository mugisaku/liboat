#ifndef GRAMK_ALBUM_HPP_INCLUDED
#define GRAMK_ALBUM_HPP_INCLUDED


#include"oat.hpp"
#include"gramk_card.hpp"
#include"gramk_painter.hpp"
#include<string>




class
Album: public oat::Widget
{
  static int  table_width ;
  static int  table_height;


  Callback  callback;

  oat::Point  cursor;

  std::vector<Card*>  table;

public:
  static void  reset_size(int  w, int  h);

  Album(Callback  cb);

  void  process_mouse(const oat::Mouse&  mouse) override;
  void  render() override;

  void   read(FILE*  f);
  void  write(FILE*  f);

  void  insert_column();
  void  remove_column();

  void  insert_row();
  void  remove_row();

  Card&  get_card(int  x, int  y) const;

  const Card*  get_current() const;


  oat::Widget*  create_operator_widget();

};




#endif




