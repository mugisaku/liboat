BASE_DIR = /usr/local




CXXFLAGS = -std=gnu++11 -I. -I.. -Werror -Wno-unused-result -I/usr/include/SDL2


ifeq ($(opt),1)
  CXXFLAGS += -Os -march=i686 -fomit-frame-pointer
  LDFLAGS  += -s
else
  CXXFLAGS += -g
endif


COMMON_LDFLAGS = -lstdc++


ifeq ($(mingw),1)
  EXE_EXT = .exe
  DIR_PREFIX = i686-w64-mingw32
  CMD_PREFIX = $(DIR_PREFIX)-
  LDFLAGS = $(COMMON_LDFLAGS) -lmingw32 -static
else
  LDFLAGS = $(COMMON_LDFLAGS)
endif




ifeq ($(emcc),1)
  CXX      = CCACHE_DIR=/tmp/ccachedir ccache emcc
  CXXFLAGS = -std=gnu++11 -I. -I.. -Werror -Wno-unused-result -Os -s USE_SDL=2
  EXE_EXT  = .html
  LDFLAGS  = 
else ifeq ($(ccache),1)
  CXX = CCACHE_DIR=/tmp/ccachedir ccache $(CMD_PREFIX)g++
else
  CXX = $(CMD_PREFIX)g++
endif



STRIP = $(CMD_PREFIX)strip
AR    = $(CMD_PREFIX)ar

CXXFLAGS += -I$(BASE_DIR)/$(DIR_PREFIX)/include
LDFLAGS  += -L$(BASE_DIR)/$(DIR_PREFIX)/lib


ifeq ($(delay),1)
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS)  $< -o $@
	sleep 1
endif


OBJ =                         \
  fcfont.o                    \
  fcfont_sample.o             \
  fcfont_characterselector.o  \
  fcfont_charactereditor.o    \
  fcfont_combinedselector.o   \
  fcfont_editor.o             \


all: $(OBJ)


clean:
	rm -f $(OBJ)




