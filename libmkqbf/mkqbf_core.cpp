#include"mkqbf_core.hpp"
#include"oat_widget.hpp"
#include<cstring>
#include<cstdio>
#include<vector>
#include<libpng/png.h>
#include<zlib.h>




namespace core{


namespace{


int  modified_flags;


using Table = Square[table_size][table_size];


Table  table;


uint8_t  image_data[image_size][image_size];

oat::Color  image_palette[image_color_number];


png_color
source_palette[image_color_number];


oat::Point
chip_point;


int  process;
int  display_phase = 8;
int  index;


void
close_read(png_structp  png, png_infop  png_info)
{
  png_read_end(png,png_info);
  png_destroy_read_struct(&png,&png_info,nullptr);
}

void
close_write(png_structp  png, png_infop  png_info)
{
  png_write_end(png,png_info);
  png_destroy_write_struct(&png,&png_info);
}


bool
test_png(FILE*  f)
{
  constexpr uint8_t
  signature[16] =
  {
    0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A,
    0x00,0x00,0x00,0x0D,0x49,0x48,0x44,0x52
  };



  fpos_t  pos;

  fgetpos(f,&pos);

    for(int  i = 0;  i < 16;  i += 1)
    {
      auto  c = fgetc(f);

        if(ferror(f) || feof(f) || (c != signature[i]))
        {
          fsetpos(f,&pos);

          return false;
        }
    }


  fsetpos(f,&pos);

  return true;
}


void
read_png(FILE*  f)
{
  png_structp  png = png_create_read_struct(PNG_LIBPNG_VER_STRING,nullptr,nullptr,nullptr);
  png_infop    png_info = png_create_info_struct(png);

  png_init_io(png,f);

  png_read_info(png,png_info);

  int       depth = png_get_bit_depth(png,png_info);
  int  color_type = png_get_color_type(png,png_info);

    if(color_type != PNG_COLOR_TYPE_PALETTE)
    {
      printf("パレットでないPNGは読めません\n");

      close_read(png,png_info);

      return;
    }


  int  w = png_get_image_width( png,png_info);
  int  h = png_get_image_height(png,png_info);

  png_color*  tmp_palette;

  int  color_number;

  png_get_PLTE(png,png_info,&tmp_palette,&color_number);

  int  n = std::min(image_color_number,color_number);

    for(int  i = 0;  i < n;  i += 1)
    {
      auto&  src = tmp_palette[i];

      source_palette[i] = src;

      image_palette[i] = oat::Color(src.red,src.green,src.blue);
    }


  png_set_packing(png);

  auto  buf = new uint8_t[w];

  w = std::min(w,image_size);
  h = std::min(h,image_size);

    for(int  y = 0;  y < h;  ++y)
    {
      png_read_row(png,buf,nullptr);

      std::memcpy(image_data[y],buf,w);
    }


  delete[] buf;

  close_read(png,png_info);
}


}




Square&  get_square(int  x, int  y){return table[y][x];}

void
change_square(int  x, int  y, bool  flag)
{
    switch(process)
    {
  case(Process::arrange_lower_chip): table[y][x].lower = chip_point;break;
  case(Process::arrange_upper_chip): table[y][x].upper = chip_point;break;
  case(Process::change_attribute  ): table[y][x].attribute = flag? (enterable_flag|index):index;break;
    }


  set_modified_flag(Update::table_flag);
}


void
change_index(int  v)
{
  index = v;
}


const oat::Color&  get_image_pixel(int  x, int  y){return image_palette[image_data[y][x]&15];}

void
change_process(int  v)
{
  process = v;

  display_phase = 8;

  set_modified_flag(Update::table_flag);
}


int  get_process(){return process;}


void
step_display()
{
    if(display_phase > 0)
    {
      display_phase -= 1;

        if(!display_phase)
        {
          display_phase = -20;

          set_modified_flag(Update::table_flag);
        }
    }

  else
    if(display_phase < 0)
    {
      display_phase += 1;

        if(!display_phase)
        {
          display_phase = 4;

          set_modified_flag(Update::table_flag);
        }
    }
}


bool  test_display(){return(display_phase > 0);}


void  set_modified_flag(int  flag){modified_flags |= flag;}


int
get_modified_flags()
{
  auto  v = modified_flags    ;
            modified_flags = 0;

  return v;
}


void
change_chip_point(int  x, int  y)
{
  chip_point.reset(x,y);

  set_modified_flag(Update::image_flag);
}


oat::Point     get_chip_point(){return chip_point;}


namespace{
std::string
qbf_path("__output.qbf");


bool
test_qbf(FILE*  f)
{
  constexpr uint8_t
  signature[4] =
  {
    'Q','B','F',0
  };


report;
    for(int  i = 0;  i < 4;  i += 1)
    {
      auto  c = fgetc(f);
printf("%c",c);
        if(ferror(f) || feof(f) || (c != signature[i]))
        {
          return false;
        }
    }


  return true;
}


}


const char*
get_filepath()
{
  auto  res = qbf_path.rfind('/');

  return (res == std::string::npos)? qbf_path.data():&qbf_path[res+1];
}


void
read(const char*  path)
{
  auto  f = fopen(path,"rb");

    if(f)
    {
        if(test_png(f))
        {
          read_png(f);
        }

      else
        if(test_qbf(f))
        {
          int  w = fgetc(f);
          int  h = fgetc(f);
          int  d = fgetc(f);

          auto   it = &table[0][0];
          auto  end = &table[h][w];

            while(it != end)
            {
              it->attribute = fgetc(f);

              it->lower.x = fgetc(f);
              it->lower.y = fgetc(f);
              it->upper.x = fgetc(f);
              it->upper.y = fgetc(f);

              it += 1;
            }


          qbf_path = path;

          set_modified_flag(Update::table_flag);
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

      auto   it = &table[0][0];
      auto  end = &table[table_size][table_size];

        while(it != end)
        {
          fputc(it->attribute,f);

          fputc(it->lower.x,f);
          fputc(it->lower.y,f);
          fputc(it->upper.x,f);
          fputc(it->upper.y,f);

          it += 1;
        }


      fclose(f);
    }
}




}




