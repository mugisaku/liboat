#include"mg_message.hpp"




namespace message{


namespace{


int  flags;


}


void
set_flag(int  flag)
{
  flags |= flag;
}


int
get_flags()
{
  auto  t = flags    ;
            flags = 0;

  return t;
}



}




