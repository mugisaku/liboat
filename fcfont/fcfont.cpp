#include"fcfont.hpp"




namespace fcfont{




namespace{


constexpr bool
is_private_use_area(char16_t  c)
{
  return((c >= 0xE000) &&
         (c <= 0xF8FF));
}


void
encode(char16_t  c, char*  buf)
{
    if(c <= 0x7F)
    {
      buf[0] = c;

      buf[1] = 0;
    }

  else
    if((c >= 0x0080) &&
       (c <= 0x07FF))
    {
      buf[0] = (0b11000000|(c>>6));
      buf[1] = (0b10000000|(c&0b111111));

      buf[2] = 0;
    }

  else
    if((c >= 0x0800) &&
       (c <= 0xFFFF))
    {
      buf[0] = (0b11100000|(c>>12));
      buf[1] = (0b10000000|((c>>6)&0b111111));
      buf[2] = (0b10000000|((c   )&0b111111));

      buf[3] = 0;
    }
}


Character
table[] =
{
#include"characters.txt"
};
}


Character*
Character::
embedded_table = table;


int
Character::
embedded_number = sizeof(table)/sizeof(*table);


Character*
Character::
pointer_table[0x10000];


void
Character::
reset_table()
{
    for(auto&  c: table)
    {
      auto&  ptr = pointer_table[c.unicode];

        if(!ptr)
        {
          pointer_table[c.unicode] = &c;
        }
    }
}


void
Character::
print_table(FILE*  f)
{
  fprintf(f,"//characters\n");

    for(auto  ptr: pointer_table)
    {
        if(!ptr)
        {
          continue;
        }


      auto&  c = *ptr;

        if(is_private_use_area(c.unicode))
        {
          fprintf(f,"{0x%04X,{",c.unicode);
        }

      else
        {
          char  buf[4];

          encode(c.unicode,buf);

          fprintf(f,"{u\'%s\',{",buf);
        }


        for(int  i = 0;  i < size;  ++i)
        {
          fprintf(f,"0x%02X,",c.data[i]);
        }


      fprintf(f,"}},\n");
    }
}




namespace{
Combined
combined_table[] =
{
#include"combineds.txt"
};
}


Combined*
Combined::
embedded_table = combined_table;


int
Combined::
embedded_number = sizeof(combined_table)/sizeof(*combined_table);


Combined*
Combined::
pointer_table[0x10000];


void
Combined::
reset_table()
{
    for(auto&  c: combined_table)
    {
      auto&  ptr = pointer_table[c.unicode];

        if(!ptr)
        {
          ptr = &c;
        }
    }
}


namespace{
void
fputc_u16be(uint16_t  c, FILE*  f)
{
  fputc(c>>8,f);
  fputc(c   ,f);
}
void
fputc_u32be(uint32_t  c, FILE*  f)
{
  fputc(c>>24,f);
  fputc(c>>16,f);
  fputc(c>> 8,f);
  fputc(c    ,f);
}
}


void
Combined::
print_table(FILE*  f)
{
  fputc( 8,f);
  fputc(12,f);
  fputc( 1,f);

  fpos_t  pos;

  fgetpos(f,&pos);

  fputc_u16be(0,f);

  int  n = 0;

    for(auto  ptr: pointer_table)
    {
        if(ptr)
        {
          auto  u = Character::pointer_table[ptr->upper];
          auto  l = Character::pointer_table[ptr->lower];

            if(u && l)
            {
              ++n;

              fputc_u16be(ptr->unicode,f);

                for(int  y = 4;  y < 8;  ++y)
                {
                  fputc(u->data[y],f);
                }


                for(int  y = 0;  y < 8;  ++y)
                {
                  fputc(l->data[y],f);
                }
            }
        }
    }



  fsetpos(f,&pos);

  fputc_u16be(n,f);
}


}




