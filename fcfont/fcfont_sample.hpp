#ifndef FCFONT_SAMPLE_HPP_INCLUDED
#define FCFONT_SAMPLE_HPP_INCLUDED


#include"oat.hpp"
#include"fcfont.hpp"


using namespace oat;


namespace fcfont{


class
Sample: public Widget
{
public:
  Sample();

  void  render() override;

};


}


#endif




