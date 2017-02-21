#ifndef GRAMK_PAINTER_HPP_INCLUDED
#define GRAMK_PAINTER_HPP_INCLUDED


#include"oat.hpp"
#include"gramk_card.hpp"
#include"gramk_clip.hpp"




constexpr int  number_of_colors = 8;


constexpr oat::Color
palette[number_of_colors] =
{
  oat::Color(0x1F),
  oat::Color(0x3F),
  oat::Color(0x5F),
  oat::Color(0x7F),
  oat::Color(0x9F),
  oat::Color(0xBF),
  oat::Color(0xDF),
  oat::Color(0xFF),
};


struct
Rect
{
  int  x;
  int  y;
  int  w;
  int  h;

};


enum class
PaintingMode
{
  draw_point,
  draw_line,
  draw_rect,
  fill_rect,
  fill_area,
  transform_area_frame,
  paste,
  layer,

};


class
Painter: public oat::Widget
{
  static constexpr int  pixel_size = 10;

  Card*  target;

  Callback  callback;

  Clip      copy_clip;
  Clip   preview_clip;
  Clip  composed_clip;

  PaintingMode  mode;

  uint8_t  current_color;

  oat::Point  point0;
  oat::Point  point1;

  Rect  selected_rect;

  bool  preview_flag;

  void  draw_selection_frame();

  void  process_draw_line(bool  button, int  color, int  x, int  y);

public:
  Painter(Callback  cb);

  void  change_target(Card&  card);

  void  change_current_color(uint8_t  color);
  void  change_mode(PaintingMode  mode_);

  Card*  get_target() const;

  uint8_t  get_current_color() const;

  void  process_mouse(const oat::Mouse&  mouse) override;
  void  render() override;

  Widget*  create_oper_widget();
  Widget*  create_mode_widget();
  Widget*  create_palette_widget();

};




#endif




