#include"oat.hpp"
#include"gramk.hpp"
#include"sdlut.hpp"


#ifdef EMSCRIPTEN
#include"emscripten.h"
#endif


using namespace oat;


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




Painter*
painter;


Album*
album;


AniBox*
anibox;


void
painter_callback(SuperCard*  card)
{
  album->need_to_redraw();
}


void
album_callback(SuperCard*  card)
{
    if(card)
    {
      painter->change_target(*card);
    }
}


const Card*
anibox_callback()
{
  return album->get_current();
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

  painter = new Painter(painter_callback);

  auto  oper = painter->create_oper_widget();
  auto  mode = painter->create_mode_widget();
  auto  plte = painter->create_palette_widget();

  auto  left = new TableRow({painter,new TableColumn({plte,mode,oper})});

  album = new Album(album_callback);

  auto  file  = album->create_file_widget();

  auto  right = new TableColumn({album,file});


  anibox = new AniBox(anibox_callback);

  auto  ctrl = anibox->create_ctrl_widget();

  master.join(new TableRow({left,right,anibox,ctrl}),0,0);

  master.update();
}


void
load(char*  path)
{
//  image::read(path);

  SDL_free(path);
}


void
main_loop()
{
  static SDL_Event  evt;

    while(SDL_PollEvent(&evt))
    {
      int  mouse_flag = false;

        switch(evt.type)
        {
          case(SDL_MOUSEBUTTONUP):
          case(SDL_MOUSEBUTTONDOWN):
            process_mouse_button(evt.button);
            mouse_flag = true;
            break;
          case(SDL_MOUSEMOTION):
            process_mouse_motion(evt.motion);
            mouse_flag = true;
            break;
          case(SDL_WINDOWEVENT):
            process_window(evt.window);
            break;
#ifndef EMSCRIPTEN
          case(SDL_DROPFILE):
            load(evt.drop.file);
            break;
#endif
          case(SDL_QUIT):
            screen.destroy();
            SDL_Quit();
            exit(0);
            break;
        }


        if(mouse_flag)
        {
          master.process(mouse);

          ButtonModule::unset_shortlived_all();
        }
    }


  auto  now = SDL_GetTicks();

 	anibox->check(now);

  static uint32_t  next_time;

    if(now >= next_time)
    {
      next_time = now+40;

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

  screen.create("animk - " __DATE__,m.get_width(),m.get_height());

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




