#ifndef MKQBF_EDITOR_HPP_INCLUDED
#define MKQBF_EDITOR_HPP_INCLUDED


#include"oat.hpp"




class
Editor: public oat::Widget
{
  oat::Point  cursor;

  void  draw_digit(int  d, const oat::Color&  color, int  x, int  y);

  void  draw_chip(const oat::Point&  chip_point, int  x_base, int  y_base);
  void  draw_attribute(int  attr, int  x_base, int  y_base);
  void  draw_bg1();
  void  draw_bg2(bool  with_attribute);
  void  draw_bg3();

public:
  Editor();

  void  process_mouse(const oat::Mouse&  mouse) override;

  void  render() override;

};





#endif




