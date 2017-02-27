#include"gramk_album.hpp"
#include<cstring>
#include<cstdio>


#ifndef EMSCRIPTEN
#include<libpng/png.h>
#include<zlib.h>
#endif



namespace{


int  color_type;
int  depth;


#ifndef EMSCRIPTEN
png_color
make_color(uint8_t  l)
{
  return png_color{l,l,l};
}


png_color
png_palette[] =
{
  {0,0,0xFF},
  make_color(0x3F),
  make_color(0x5F),
  make_color(0x7F),
  make_color(0x9F),
  make_color(0xBF),
  make_color(0xDF),
  make_color(0xFF),
  make_color(0x1F),
  make_color(0x3F),
  make_color(0x5F),
  make_color(0x7F),
  make_color(0x9F),
  make_color(0xBF),
  make_color(0xDF),
  make_color(0xFF),
};


void
close_read(png_structp  png, png_infop  png_info, FILE*  f)
{
  png_read_end(png,png_info);
  png_destroy_read_struct(&png,&png_info,nullptr);

  fclose(f);
}


void
close_write(png_structp  png, png_infop  png_info, FILE*  f)
{
  png_write_end(png,png_info);
  png_destroy_write_struct(&png,&png_info);

  fclose(f);
}


int
min(int  a, int  b)
{
  return(a < b)? a:b;
}


#endif


}




namespace{


bool
test_png(FILE*  f)
{
  constexpr uint8_t
  png_signature[16] =
  {
    0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A,
    0x00,0x00,0x00,0x0D,0x49,0x48,0x44,0x52
  };



  fpos_t  pos;

  fgetpos(f,&pos);

    for(int  i = 0;  i < 16;  i += 1)
    {
      auto  c = fgetc(f);

        if(ferror(f) || feof(f) || (c != png_signature[i]))
        {
          return false;
        }
    }


  fsetpos(f,&pos);

  return true;
}


}


void
Album::
read(FILE*  f)
{
#ifndef EMSCRIPTEN
    if(test_png(f))
    {
      png_structp  png = png_create_read_struct(PNG_LIBPNG_VER_STRING,nullptr,nullptr,nullptr);
      png_infop    png_info = png_create_info_struct(png);

      png_init_io(png,f);

      png_read_info(png,png_info);

      depth = png_get_bit_depth(png,png_info);
      color_type = png_get_color_type(png,png_info);

        if(color_type != PNG_COLOR_TYPE_PALETTE)
        {
          printf("パレットでないPNGは読めません\n");

          close_read(png,png_info,f);

          throw;
        }


      auto  w = png_get_image_width( png,png_info);
      auto  h = png_get_image_height(png,png_info);

      auto  png_table_w = (w/Card::width );
      auto  png_table_h = (h/Card::height);

      auto  tt_w = min(png_table_w,table_width );
      auto  tt_h = min(png_table_h,table_height);

      png_color*  tmp_palette;

      int  color_number;

      png_get_PLTE(png,png_info,&tmp_palette,&color_number);


      png_set_packing(png);

      std::vector<uint8_t>  buffer(w*h);

        for(int  y = 0;  y < h;  ++y)
        {
          png_read_row(png,&buffer[w*y],nullptr);
        }


        for(int  y = 0;  y < tt_h;  ++y){
        for(int  x = 0;  x < tt_w;  ++x){
          auto&  c = *table[(table_width*y)+x];

          c.unset_recording_flag();

            for(int  yy = 0;  yy < Card::height;  ++yy){
            for(int  xx = 0;  xx < Card::width ;  ++xx){
              auto  v = buffer[(w*Card::height*y)+(w*yy)+(Card::width*x)+xx];

              c.put_color(v,xx,yy);
            }}


          c.set_recording_flag();
        }}


      close_read(png,png_info,f);
	   }
#endif
}


void
Album::
write(FILE*  f)
{
#ifndef EMSCRIPTEN
  png_structp  png = png_create_write_struct(PNG_LIBPNG_VER_STRING,nullptr,nullptr,nullptr);

  png_infop  png_info = png_create_info_struct(png);

  png_init_io(png,f);

  png_set_compression_level(png,Z_BEST_COMPRESSION);

  const int  w = Card::width*table_width;
  const int  h = Card::height*table_height;

  png_set_IHDR(png,png_info,w,h,4,
               PNG_COLOR_TYPE_PALETTE,
               PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);

  png_set_PLTE(png,png_info,png_palette,16);

  png_write_info(png,png_info);

  png_set_packing(png);

  std::vector<uint8_t>  buffer(w*h);

    for(int  y = 0;  y < table_height;  ++y){
    for(int  x = 0;  x < table_width ;  ++x){
      auto&  c = *table[(table_width*y)+x];

        for(int  yy = 0;  yy < Card::height;  ++yy){
        for(int  xx = 0;  xx < Card::width ;  ++xx){
          buffer[(w*Card::height*y)+(w*yy)+(Card::width*x)+xx] = c.get_color(xx,yy);
        }}
    }}


    for(int  y = 0;  y < h;  ++y)
    {
      png_write_row(png,&buffer[w*y]);
    }


  close_write(png,png_info,f);
#endif
}




