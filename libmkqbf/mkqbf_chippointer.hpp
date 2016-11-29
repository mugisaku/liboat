#ifndef MKQBF_CHIPPOINTER_HPP_INCLUDED
#define MKQBF_CHIPPOINTER_HPP_INCLUDED


#include"oat.hpp"




class
ChipPointer: public oat::Widget
{
  oat::Point  cursor;

public:
  ChipPointer();

  void  process_mouse(const oat::Mouse&  mouse) override;

  void  render() override;

};





#endif




