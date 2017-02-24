#ifndef OAT_UNICODE_HPP
#define OAT_UNICODE_HPP


#include<cstdint>
#include<string>


namespace oat{
namespace unicode{


struct
UTF8Chunk
{
  char  data[4];

  UTF8Chunk(char16_t  c);

  UTF8Chunk&  operator=(char16_t  c);

};


std::u16string  to_u16string(const std::string&  src);


}}


#endif




