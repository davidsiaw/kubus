CLANGXX=clang++
CXX=g++
FLAGS=-g -std=c++11
SRC=`ls ../src/*.cpp`
INC=`../../libs/sources/build/bin/sdl-config --cflags` -I../src/ -I../../libs/sources/boost/ -I../../libs/sources/build/include
LIBS=`../../libs/sources/build/bin/sdl-config --libs` -L../../libs/sources/build/lib -lSDL_ttf -lfreetype -lSDL_image -lpng -lz -lX11 -lXmu -lXi -lGL -lGLU -lXext -lGLEW
MACLIBS= -stdlib=libc++ -framework opengl
OUTPUT=-o akari

all:
	$(CXX) $(FLAGS) $(SRC) $(INC) $(LIBS) $(OUTPUT)

macos:
	$(CLANGXX) $(FLAGS) $(SRC) $(INC) $(LIBS) $(MACLIBS) $(OUTPUT) 


clean:

