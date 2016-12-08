#include"oat.hpp"
#include"sdlut.hpp"
#include"libmg/mg_message.hpp"
#include"libmg/mg_image.hpp"
#include"libmg/mg_color_selection.hpp"
#include"libmg/mg_tool_selection.hpp"
#include"libmg/mg_area_selection.hpp"
#include"libmg/mg_canvas.hpp"
#include"libmg/mg_board.hpp"


#ifdef EMSCRIPTEN
#include"emscripten.h"
#endif


using namespace oat;


constexpr int  chip_size = 24;


sdlut::Screen
screen;


int
modified;


Mouse
mouse;


void
update_screen()
{
  screen.lock();

  auto&  m = master.get_module();

    for(int  y = 0;  y < m.get_height();  ++y)
    {
      auto  row = screen.get_row(y);

        for(int  x = 0;  x < m.get_width();  ++x)
        {
          auto&  pix = m.get_element(x,y);

          auto  color = screen.map_rgb(pix.r,pix.g,pix.b);

          row.put(color,x);
        }
    }


  screen.unlock();
  screen.update();
}


void
process_mouse_button(const SDL_MouseButtonEvent&  evt)
{
  mouse.change_point(Point(evt.x,evt.y));

    if(evt.button == SDL_BUTTON_LEFT)
    {
        if(evt.state == SDL_PRESSED){mouse.left.press();}
      else                          {mouse.left.unpress();}
    }

  else
    {
        if(evt.state == SDL_PRESSED){mouse.right.press();}
      else                          {mouse.right.unpress();}
    }
}


void
process_mouse_motion(const SDL_MouseMotionEvent&  evt)
{
  mouse.change_point(Point(evt.x,evt.y));


    if(evt.state&SDL_BUTTON_LMASK){mouse.left.press();}
  else                            {mouse.left.unpress();}

    if(evt.state&SDL_BUTTON_RMASK){mouse.right.press();}
  else                            {mouse.right.unpress();}
}


void
process_window(const SDL_WindowEvent&  evt)
{
    switch(evt.event)
    {
      case(SDL_WINDOWEVENT_EXPOSED):
        modified = 1;
        break;
    }
}




Widget*  canvas;
Widget*  panel;
NoteBook*  notebook;


void
change(Button&  btn)
{
    if(btn->test_pressed())
    {
        switch(notebook->get_top_index())
        {
      case(0):
          notebook->change_top(1);
          area_selection::reset(board::table_size,board::table_size);
          break;
      case(1):
          notebook->change_top(0);
          area_selection::reset(chip_size,chip_size);
          break;
        }
    }
}


void
construct_widgets()
{
  master.style.background_color = const_color::gray;

  default_style.background_color = const_color::dark_gray;
  default_style.font_color       = const_color::white;
  default_style.border_width = 1;
  default_style.border_color = const_color::white;
  default_style.left_padding   = 2;
  default_style.right_padding  = 2;
  default_style.top_padding    = 2;
  default_style.bottom_padding = 2;


  image::set_parameter(chip_size,chip_size,1);


  canvas = new Canvas;
  panel = board::create_widget();

  auto  mkptrn_left  = new TableColumn({color_selection::create_widget(),tool_selection::create_widget()});
  auto  mkptrn_upper = new TableRow({mkptrn_left,canvas});
  auto  mkptrn       = new TableColumn({mkptrn_upper,image::create_edit_widget()});


  auto  img = image::create_main_widget();


  notebook = new NoteBook;

  notebook->join(mkptrn,0,0);
  notebook->join(panel,0,0);


  auto  left = new TableColumn({new Button(new Text(u"切り替え"),change),notebook});

  master.join(new TableRow({left,img}),0,0);

  master.update();
}


void
load(char*  path)
{
  image::read(path);
  board::read(path);

  message::set_flag(message::image_modified_flag);

  SDL_free(path);
}


void
main_loop()
{
  static SDL_Event  evt;

  int  mouse_input = 0;

    while(SDL_PollEvent(&evt))
    {
        switch(evt.type)
        {
          case(SDL_MOUSEBUTTONUP):
          case(SDL_MOUSEBUTTONDOWN):
            mouse_input = 1;
            process_mouse_button(evt.button);
            break;
          case(SDL_MOUSEMOTION):
            mouse_input = 1;
            process_mouse_motion(evt.motion);
            break;
          case(SDL_WINDOWEVENT):
            process_window(evt.window);
            break;
          case(SDL_DROPFILE):
            load(evt.drop.file);
            break;
          case(SDL_QUIT):
            screen.destroy();
            SDL_Quit();
            exit(0);
            break;
        }
    }


    if(mouse_input)
    {
      master.process(mouse);

      auto  v = message::get_flags();

        if(v&message::image_modified_flag)
        {
          canvas->need_to_redraw();
          panel->need_to_redraw();
        }


      mouse_input = 0;
    }


  static uint32_t  next_time;

  auto  now = SDL_GetTicks();

    if(now >= next_time)
    {
      next_time = now+120;

        if(master.update() || modified)
        {
          update_screen();

          modified = 0;
        }
    }
}


int
main(int  argc,  char**  argv)
{
  construct_widgets();

  SDL_Init(SDL_INIT_VIDEO);

  auto&  m = oat::master.get_module();

  screen.create("mkbg " __DATE__,m.get_width(),m.get_height());

  update_screen();

#ifdef EMSCRIPTEN
  emscripten_set_main_loop(main_loop,-1,false);
#else
    for(;;)
    {
      main_loop();

      SDL_Delay(20);
    }
#endif


  return 0;
}




