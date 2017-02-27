#ifndef GRAMK_DRAWING_HPP_INCLUDED
#define GRAMK_DRAWING_HPP_INCLUDED


#include"oat.hpp"
#include<vector>




void  draw_line(   const oat::Point&  p0, const oat::Point&  p1, std::vector<oat::Point>&  buf);
void  draw_ellipse(const oat::Point&  p0, const oat::Point&  p1, std::vector<oat::Point>&  buf);




#endif




