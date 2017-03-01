#ifndef GRAMK_CARD_HPP_INCLUDED
#define GRAMK_CARD_HPP_INCLUDED


#include<cstdint>
#include"oat.hpp"
#include"gramk_packet.hpp"
#include"gramk_rect.hpp"
#include<forward_list>




class
Card
{
public:
  static constexpr int  width  = 24;
  static constexpr int  height = 48;

  static const Rect  whole_rect;

protected:
  uint8_t  color_table[height][width];

  bool  recording_flag;

  std::forward_list<Packet>  log_list;

  std::vector<Dot>  operation_log;

  void  subroutine_for_fill_area(int  color, int  x, int  y, int  target);

public:
  static void  transfer(const Card&  src, const Rect&  src_rect,
                              Card&  dst, int  dst_x, int  dst_y, bool  overwrite);


  Card(bool  rec=false);
  Card(const Card&  rhs);

  Card&  operator=(const Card&  rhs);

  uint8_t  get_color(                int  x, int  y) const;
  void     put_color(uint8_t  color, int  x, int  y)      ;


  void  clear();

  void    set_recording_flag();
  void  unset_recording_flag();

  void  undo();

  void  prepare_new_log(bool  solid_flag=false);

  void  render(int  src_w, int  src_h, oat::Widget&  dst, int  dst_x, int  dst_y, int  pixel_size=1) const;


  void  revolve(             const Rect&  rect);
  void  reverse_horizontally(const Rect&  rect);
  void  reverse_vertically(  const Rect&  rect);
  void  mirror_vertically(   const Rect&  rect);

  void  shift_up(    const Rect&  rect, bool  rotate=false);
  void  shift_left(  const Rect&  rect, bool  rotate=false);
  void  shift_right( const Rect&  rect, bool  rotate=false);
  void  shift_down(  const Rect&  rect, bool  rotate=false);

  void  fill_area(int  color, int  x, int  y);


};


#endif




