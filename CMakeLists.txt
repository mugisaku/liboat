cmake_minimum_required(VERSION 2.8)
project(oat)


find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "CCACHE_DIR=/tmp/ccachedir ccache")
endif(CCACHE_FOUND)


set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_COMPILER  gcc)
set(CMAKE_C_FLAGS   "-std=c11 -Werror -march=core2")
set(CMAKE_C_FLAGS_RELEASE "-Os -fomit-frame-pointer")
set(CMAKE_C_FLAGS_DEBUG   "-Og -g")
set(CMAKE_CXX_COMPILER  g++)
set(CMAKE_CXX_FLAGS "-std=c++11 -Werror -march=core2")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -fomit-frame-pointer")
set(CMAKE_CXX_FLAGS_DEBUG   "-Og -g")
set(CMAKE_CXX_LINK_FLAGS  "-lstdc++ -lz -lpng -lSDL2 -lSDL2main")




set(OAT_SOURCES
  core/oat.cpp
  core/oat_unicode.cpp
  core/oat_font.cpp
  core/oat_color.cpp
  core/oat_box.cpp
  core/oat_widget.cpp
  core/oat_widget_render.cpp
  core/oat_container.cpp
  core/oat_notebook.cpp
  core/oat_iconmodule.cpp
  core/oat_icon.cpp
  core/oat_image.cpp
  core/oat_image_directcolor.cpp
  core/oat_image_indexcolor.cpp
  core/oat_text.cpp
  core/oat_textbox.cpp
  core/oat_dial.cpp
  core/oat_cross.cpp
  core/oat_buttonmodule.cpp
  core/oat_button.cpp
  core/oat_table.cpp
  core/oat_checkform.cpp
  core/oat_master.cpp
)


set(GRAMK_SOURCES
  gramk/gramk_card.cpp
  gramk/gramk_card__log.cpp
  gramk/gramk_card__draw.cpp
  gramk/gramk_card__operate.cpp
  gramk/gramk_card__fill_area.cpp
  gramk/gramk_painter.cpp
  gramk/gramk_painter__move_corner.cpp
  gramk/gramk_painter__create_oper_widget.cpp
  gramk/gramk_painter__create_mode_widget.cpp
  gramk/gramk_painter__create_palette_widget.cpp
  gramk/gramk_album.cpp
  gramk/gramk_album__file.cpp
  gramk/gramk_anibox.cpp
  gramk/gramk_pathholder.cpp
)


include_directories(./core)
include_directories(./gramk)
add_executable(Gramk gramk.cpp ${OAT_SOURCES} ${GRAMK_SOURCES})




