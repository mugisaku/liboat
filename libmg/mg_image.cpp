#include"mg_image.hpp"
#include"mg_area_selection.hpp"
#include<cstring>
#include<cstdio>
#include<vector>
#include<libpng/png.h>
#include<zlib.h>




namespace image{


namespace{


int  chip_width;
int  chip_height;
int  chip_number;
int  chip_index;

Frame  frame;


int  color_type;

int  depth;


png_color
make_color(uint8_t  l)
{
  return png_color{l,l,l};
}


png_color
palette[] =
{
  make_color(0x1F),
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


uint8_t
pixels[size][size];


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


}




void
set_parameter(int  w, int  h, int  n)
{
  chip_width  = w;
  chip_height = h;
  chip_number = n;

  frame.x = 0;
  frame.y = 0;
  frame.w = chip_width*chip_number;
  frame.h = chip_height;

  area_selection::reset();
}




void
change_chip_index(int  v)
{
  chip_index = v;
}


int  get_chip_width(){return chip_width;}
int  get_chip_height(){return chip_height;}
int  get_chip_index(){return chip_index;}
int  get_chip_number(){return chip_number;}




const Frame&
get_frame()
{
  return frame;
}




void
change_frame_point(const oat::Point&  pt)
{
  frame.x = pt.x;
  frame.y = pt.y;
}




void
put_pixel(int  color_index, int  x, int  y)
{
  pixels[frame.y+y][frame.x+(chip_width*chip_index)+x] = color_index;
}


int
get_pixel(int  x, int  y)
{
  return pixels[y][x];
}


int
get_chip_pixel(int  x, int  y)
{
  return get_pixel(frame.x+(chip_width*chip_index)+x,frame.y+y);
}


int
get_frame_pixel(int  x, int  y)
{
  return get_pixel(frame.x+x,frame.y+y);
}




namespace{
std::string
png_path("__output.png");


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


const char*
get_filepath()
{
  auto  res = png_path.rfind('/');

  return (res == std::string::npos)? png_path.data():&png_path[res+1];
}


void
read(const char*  path)
{
  auto  f = fopen(path,"rb");

    if(f && test_png(f))
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

        if(w > size){w = size;}
        if(h > size){h = size;}


      png_color*  tmp_palette;

      int  color_number;

      png_get_PLTE(png,png_info,&tmp_palette,&color_number);


      png_set_packing(png);

        for(int  y = 0;  y < h;  ++y)
        {
          png_read_row(png,pixels[y],nullptr);
        }


      close_read(png,png_info,f);

      png_path = path;
	   }
}



void
write()
{
  auto  f = fopen(png_path.data(),"wb");

    if(f)
    {
      png_structp  png = png_create_write_struct(PNG_LIBPNG_VER_STRING,nullptr,nullptr,nullptr);

      png_infop  png_info = png_create_info_struct(png);

      png_init_io(png,f);

      png_set_compression_level(png,Z_BEST_COMPRESSION);

      png_set_IHDR(png,png_info,size,size,4,
                   PNG_COLOR_TYPE_PALETTE,
                   PNG_INTERLACE_NONE,
                   PNG_COMPRESSION_TYPE_DEFAULT,
                   PNG_FILTER_TYPE_DEFAULT);

      png_set_PLTE(png,png_info,palette,16);

      png_write_info(png,png_info);

      png_set_packing(png);

        for(int  y = 0;  y < size;  ++y)
        {
          png_write_row(png,pixels[y]);
        }


      close_write(png,png_info,f);
    }
}




}




