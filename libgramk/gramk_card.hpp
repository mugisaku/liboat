#ifndef GRAMK_CARD_HPP_INCLUDED
#define GRAMK_CARD_HPP_INCLUDED


#include"oat.hpp"
#include"gramk_packet.hpp"
#include<forward_list>




struct Clip;
struct Card;


using Callback = void  (*)(Card*  card);


class
Card
{
public:
  static constexpr int   width = 24;
  static constexpr int  height = 48;


private:
  uint8_t  pixels[height][width];

  std::forward_list<Packet>  log_list;

  std::vector<Dot>  operation_log;

  void  subroutine_for_fill_area(int  color, int  x, int  y, int  target);

public:
  Card();
  Card(const Card&  rhs);

  Card&  operator=(const Card&  rhs);

  void  put(                int  color, int  x, int  y);
  void  put_without_logging(int  color, int  x, int  y);
  void  put(const Clip&  clip, int  x, int  y, bool  overwrite);

  void  revolve(             int  x, int  y, int  w, int  h);
  void  reverse_horizontally(int  x, int  y, int  w, int  h);
  void  reverse_vertically(  int  x, int  y, int  w, int  h);
  void  mirror_vertically(   int  x, int  y, int  w, int  h);

  void  shift_up(    int  x, int  y, int  w, int  h);
  void  shift_left(  int  x, int  y, int  w, int  h);
  void  shift_right( int  x, int  y, int  w, int  h);
  void  shift_down(  int  x, int  y, int  w, int  h);
  void  rotate_up(   int  x, int  y, int  w, int  h);
  void  rotate_left( int  x, int  y, int  w, int  h);
  void  rotate_right(int  x, int  y, int  w, int  h);
  void  rotate_down( int  x, int  y, int  w, int  h);

  void  draw_rect(int  color, int  x, int  y, int  w, int  h);
  void  fill_rect(int  color, int  x, int  y, int  w, int  h);
  void  fill_area(int  color, int  x, int  y);

  uint8_t  get(int  x, int  y) const;

  void  get(Clip&  clip, int  x, int  y, int  w, int  h) const;

  void  undo();

  void  prepare_new_log(bool  solid_flag=false);

  void  clear();

  void  draw(oat::Widget&  dst, int  x, int  y) const;

};


#endif




