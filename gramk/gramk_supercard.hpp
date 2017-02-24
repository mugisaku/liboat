#ifndef GRAMK_SUPERCARD_HPP_INCLUDED
#define GRAMK_SUPERCARD_HPP_INCLUDED


#include"oat.hpp"
#include"gramk_packet.hpp"
#include"gramk_card.hpp"
#include"gramk_drawing.hpp"
#include<forward_list>




struct Clip;


class
SuperCard: public Card
{
public:
  static constexpr int   width = Card::fixed_width;
  static constexpr int  height = Card::fixed_height;

private:

  std::forward_list<Packet>  log_list;

  std::vector<Dot>  operation_log;

  void  subroutine_for_fill_area(int  color, int  x, int  y, int  target);

public:
  SuperCard();
  SuperCard(const SuperCard&  rhs);

  SuperCard&  operator=(const SuperCard&  rhs);

  void  put(                int  color, int  x, int  y);
  void  put_without_logging(int  color, int  x, int  y);
  void  put(const Clip&  clip, int  x, int  y, bool  overwrite);

  void  revolve(             const Rect&  rect);
  void  reverse_horizontally(const Rect&  rect);
  void  reverse_vertically(  const Rect&  rect);
  void  mirror_vertically(   const Rect&  rect);

  void  shift_up(    const Rect&  rect);
  void  shift_left(  const Rect&  rect);
  void  shift_right( const Rect&  rect);
  void  shift_down(  const Rect&  rect);
  void  rotate_up(   const Rect&  rect);
  void  rotate_left( const Rect&  rect);
  void  rotate_right(const Rect&  rect);
  void  rotate_down( const Rect&  rect);

  void  fill_area(int  color, int  x, int  y);

  void  get(Clip&  clip, const Rect&  rect) const;

  void  undo();
  void  clear();

  void  prepare_new_log(bool  solid_flag=false);

};


#endif




