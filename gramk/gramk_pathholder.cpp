#include"gramk_pathholder.hpp"




PathHolder::
PathHolder():
filepath("__new.png"),
TextBox(16,1)
{
  change_string(u"__new.png");
}




void
PathHolder::
set(const char*  s)
{
  filepath = s;

  auto  res = filepath.rfind('/');

  auto  p = ((res == std::string::npos)? filepath.data():&filepath[res+1]);

  std::string  tmps(p);

  change_string(oat::unicode::to_u16string(tmps));
}


const std::string&
PathHolder::
get() const
{
  return filepath;
}




