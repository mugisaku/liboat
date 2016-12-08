#include"mg_board.hpp"
#include"mg_image.hpp"
#include<cstring>




namespace board{


namespace{
std::string
qbf_path("__new.qbf");


bool
test_qbf(FILE*  f)
{
  constexpr uint8_t
  signature[4] =
  {
    'Q','B','F',0
  };


    for(int  i = 0;  i < 4;  i += 1)
    {
      auto  c = fgetc(f);

        if(ferror(f) || feof(f) || (c != signature[i]))
        {
          return false;
        }
    }


  return true;
}


}


void
read(const char*  path)
{
  auto  f = fopen(path,"rb");

    if(f)
    {
        if(test_qbf(f))
        {
          int  w = fgetc(f);
          int  h = fgetc(f);
          int  d = fgetc(f);

          auto  buf = new Square[w*h];

          auto         buf_it = buf;
          auto  const buf_end = buf+(w*h);

          int  chip_w = image::get_chip_width();
          int  chip_h = image::get_chip_height();

            while(buf_it != buf_end)
            {
              buf_it->attribute = fgetc(f);

              buf_it->lower.x = chip_w*fgetc(f);
              buf_it->lower.y = chip_h*fgetc(f);
              buf_it->upper.x = chip_w*fgetc(f);
              buf_it->upper.y = chip_h*fgetc(f);

              buf_it += 1;
            }


          const int  dst_w = std::min(w,table_size);
          const int  dst_h = std::min(h,table_size);

            for(int  y = 0;  y < dst_h;  y += 1){
            for(int  x = 0;  x < dst_w;  x += 1){
              put_square(buf[(w*y)+x],x,y);
            }}


          delete[] buf;

          qbf_path = path;


          auto  p = std::strrchr(path,'/');

          change_path_text(oat::unicode::to_u16string(p? (p+1):path));
        }


      fclose(f);
    }
}


void
write()
{
  auto  f = fopen(qbf_path.data(),"wb");

    if(f)
    {
      fputc('Q',f);
      fputc('B',f);
      fputc('F',f);
      fputc(0,f);
      fputc(table_size,f);
      fputc(table_size,f);
      fputc(2,f);

      auto   it = &get_square(0,0);
      auto  end = &get_square(table_size,table_size);

      int  chip_w = image::get_chip_width();
      int  chip_h = image::get_chip_height();

        while(it != end)
        {
          fputc(it->attribute,f);

          fputc(it->lower.x/chip_w,f);
          fputc(it->lower.y/chip_h,f);
          fputc(it->upper.x/chip_w,f);
          fputc(it->upper.y/chip_h,f);

          it += 1;
        }


      fclose(f);
    }
}




}




