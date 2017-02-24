#ifndef GRAMK_PATHHOLDER_HPP_INCLUDED
#define GRAMK_PATHHOLDER_HPP_INCLUDED


#include"oat.hpp"




class
PathHolder: public oat::TextBox
{
  std::string  filepath;

public:
  PathHolder();

  void  set(const char*  s);
  const std::string&  get() const;

};




#endif




