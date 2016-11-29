#ifndef MKQBF_EDITOR_HPP_INCLUDED
#define MKQBF_EDITOR_HPP_INCLUDED


#include"oat.hpp"




class
Editor: public oat::Widget
{
  oat::Point  cursor;

  void  draw_digit(int  d, const oat::Color&  color, int  x, int  y);

public:
  Editor();

  void  process_mouse(const oat::Mouse&  mouse) override;

  void  render() override;

};





#endif




