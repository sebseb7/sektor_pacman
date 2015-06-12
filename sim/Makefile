UNAME := $(shell uname)

COMPILER = gcc


FLAGS= -I. -Ilibs -lportmidi --std=gnu99 -Wall  -funsigned-char -Wundef -Wsign-compare  -Wstrict-prototypes -lftdi1
LDFLAGS=

ifeq ($(UNAME), Darwin)
	COMPILER = clang
	FLAGS   += -Qunused-arguments
	
	FLAGS   += `sdl-config --cflags` 
	LDFLAGS += `sdl-config --libs`  
endif

ifeq ($(UNAME), Linux)
	FLAGS   += `sdl-config --cflags`
	LDFLAGS +=  -lSDL  
endif


SOURCES=$(wildcard ../animations/*.c)

LIB_SOURCES=$(wildcard mcugui/*.c libs/*.c)
LIB_HEADERS=$(wildcard mcugui/*.h libs/*.h)

all: pacman


clean:
	rm -f pacman


pacman: $(SOURCES) $(LIB_SOURCES) $(LIB_HEADERS) main.c main.h Makefile 
	@echo "  \033[1;34mCompile \033[0m -> \033[1;33m pacman \033[0m"
	@$(COMPILER) -DFULL=1 $(FLAGS) $(LIB_SOURCES) $(SOURCES) $(LDFLAGS) main.c -o pacman -I. 

.PHONY : clean all 

