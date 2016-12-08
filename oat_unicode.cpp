#include"oat_unicode.hpp"




namespace oat{
namespace unicode{


UTF8Chunk::
UTF8Chunk(char16_t  c)
{
  *this = c;
}




UTF8Chunk&
UTF8Chunk::
operator=(char16_t  c)
{
  char*  p = data;

    if(c <= 0x7F)
    {
      *p++ = c;
    }

  else
    if((c >= 0x0080) &&
       (c <= 0x07FF))
    {
      *p++ = (0b11000000|(c>>6));
      *p++ = (0b10000000|(c&0b111111));
    }

  else
    if((c >= 0x0800) &&
       (c <= 0xFFFF))
    {
      *p++ = (0b11100000|(c>>12));
      *p++ = (0b10000000|((c>>6)&0b111111));
      *p++ = (0b10000000|((c   )&0b111111));
    }


  *p = 0;

  return *this;
}




size_t
get_utf8_byte_number(int  c)
{
       if(!(c>>7)          ){return 1;}
  else if( (c>>4) == 0b1110){return 3;}
  else if( (c>>5) == 0b110 ){return 2;}
  else if( (c>>6) == 0b10  ){return 1;}

  throw 0;
}


std::u16string
to_u16string(const std::string&  src)
{
  std::u16string  s;

  auto  p = src.data();

    try
    {
        for(auto  c: src)
        {
          const size_t  n = get_utf8_byte_number(*p);

            switch(n)
            {
              case(1): s += ((p[0]             )                                    );break;
              case(2): s += ((p[0]&0b11111)<< 6)|((p[1]&0b111111)                   );break;
              case(3): s += ((p[0]&0b01111)<<12)|((p[1]&0b111111)<<6)|(p[2]&0b111111);break;
            }


          p += n;
        }
    }


    catch(...)
    {
      printf("対応していないUTF8文字です\n");

      throw;
    }


  return std::move(s);
}


}}




