#ifndef GRAMK_ALBUM_HPP_INCLUDED
#define GRAMK_ALBUM_HPP_INCLUDED


#include"oat.hpp"
#include"gramk_card.hpp"
#include"gramk_supercard.hpp"
#include"gramk_painter.hpp"
#include<string>




class
Album: public oat::Widget
{
  static constexpr int table_width  = 12;
  static constexpr int table_height =  8;


  Callback  callback;

  oat::Point  cursor;

  std::vector<SuperCard*>  table;

  std::string  png_path;

public:
  Album(Callback  cb);

  void  process_mouse(const oat::Mouse&  mouse) override;
  void  render() override;

  void   read(const char*  path);
  void  write(                 );

  const SuperCard*  get_current() const;

  const char*  get_filepath() const;

  oat::Widget*  create_file_widget();

};




#endif



