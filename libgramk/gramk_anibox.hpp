#ifndef GRAMK_ANIBOX_HPP_INCLUDED
#define GRAMK_ANIBOX_HPP_INCLUDED


#include"oat.hpp"
#include"gramk_card.hpp"




using GetCard = const Card*  (*)();


class
AniBox: public oat::Widget
{
  using List = std::vector<const Card*>;

  List  list;

  int  current;

  GetCard  callback;

  uint32_t      last_time;
  uint32_t  interval_time;

public:
  AniBox(GetCard  cb);

  void  push();
  void  pop();
  void  clear();

  void  check(uint32_t  now);

  void  render() override;

  oat::Widget*  create_ctrl_widget();

};





#endif




