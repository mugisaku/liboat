#include"oat_font.hpp"
#include<algorithm>
#include<cstdlib>




namespace oat{
namespace font{




namespace{


const uint16_t*
table[0x10000];


FILE*
open_data()
{
  auto  f = fopen("font.bin","rb");

    if(f)
    {
      return f;
    }


  auto  v = std::getenv("OAT_DIR");

    if(v)
    {
      char  buf[256];

      snprintf(buf,sizeof(buf),"%s/font.bin",v);

      f = fopen(buf,"rb");

        if(f)
        {
          return f;
        }
    }


  return nullptr;
}


struct
Initializer
{
  Initializer();

};


Initializer::
Initializer()
{
  enum{
    fullwidth_start = 0xFF00,
    fullwidth_end   = 0xFF5F,
  };


  auto  f = open_data();

    if(!f)
    {
      return;
    }


  uint16_t  n  = (fgetc(f)<<8);
            n |= (fgetc(f)   );

  auto  p = new uint16_t[14*n];

    while(n--)
    {
      uint16_t  unicode  = (fgetc(f)<<8);
                unicode |= (fgetc(f)   );

      table[unicode] = p;

        for(auto  i = 0;  i < 14;  i++)
        {
          *p    = (fgetc(f)<<8);
          *p++ |= (fgetc(f)   );
        }
    }


  fclose(f);

    if(!table[' '])
    {
      table[' '] = table[u'　'];
    }


    if(!table['-'])
    {
      table['-'] = table[u'─'];
    }


    for(int  c = fullwidth_start;  c < fullwidth_end;  ++c)
    {
      auto&  dst = table[c-fullwidth_start+' '];

      auto  src = table[c];

        if(!dst)
        {
          dst = src;
        }
    }
}


Initializer
init;


}




const uint16_t*
get_data(int  c)
{
  return table[c];
}



}}





