#ifndef GRAMK_PAINTER_HPP_INCLUDED
#define GRAMK_PAINTER_HPP_INCLUDED


#include"oat.hpp"
#include"gramk_supercard.hpp"
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


using Callback = void  (*)(SuperCard*  card);


class
Painter: public oat::Widget
{
  static constexpr int  pixel_size = 10;

  SuperCard*  target;

  Callback  callback;

  Clip       copy_clip;
  Clip  temporary_clip;

  PaintingMode  mode;

  uint8_t  current_color;

  bool  composing_flag;
  bool   selected_flag;

  oat::Point  point0;
  oat::Point  point1;

  Rect   drawing_rect;
  Rect  selected_rect;

  void  draw_selection_frame();

  void  process_draw_line(bool  button, int  color, int  x, int  y);

public:
  Painter(Callback  cb);

  void  change_target(SuperCard&  card);

  void  change_current_color(uint8_t  color);
  void  change_mode(PaintingMode  mode_);

  SuperCard*  get_target() const;

  uint8_t  get_current_color() const;

  const Rect&  get_drawing_rect() const;

  void  copy();

  void  process_mouse(const oat::Mouse&  mouse) override;
  void  render() override;

  Widget*  create_oper_widget();
  Widget*  create_mode_widget();
  Widget*  create_palette_widget();

};




#endif




