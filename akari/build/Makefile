CLANGXX=clang++
CXX=g++
FLAGS=-g -std=gnu++0x
SRC=`ls ../src/*.cpp`

INC=`../../libs/sources/build/bin/sdl-config --cflags` -I../src/ -I../../libs/sources/boost/ -I../../libs/sources/build/include
LIBS=`../../libs/sources/build/bin/sdl-config --libs` -L../../libs/sources/build/lib -lSDL_ttf -lfreetype -lSDL_image -lpng -lz -lX11 -lXmu -lXi -lGL -lGLU -lXext -lGLEW
MACLIBS= -stdlib=libc++ -framework opengl
OUTPUT= akari

PACKERSRC=../packer/main.cpp ../packer/pngfuncs.c
PACKEROUTPUT=pack

akari:
	$(CXX) $(FLAGS) $(SRC) $(INC) $(LIBS) -o $(OUTPUT)
	
macosx:
	$(CLANGXX) $(FLAGS) $(SRC) $(INC) $(LIBS) -o $(OUTPUT)

packer:
	$(CXX) $(FLAGS) $(PACKERSRC) $(INC) $(LIBS) -o $(PACKEROUTPUT)

mm:
	$(CXX) $(FLAGS) -MM $(SRC) $(INC)

clean:
	rm $(OUTPUT)
	rm $(PACKEROUTPUT)
