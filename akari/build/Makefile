CXX=clang++
FLAGS=-g -std=c++11 -stdlib=libc++
SRC=`ls ../src/*.cpp`
INC=-I ../src/ -I ../../libs/sources/boost_1_53_0/ -I ../../libs/sources/SDL_image-1.2.10/ -I ../../libs/sources/SDL_ttf-2.0.10/ -I ../../libs/sources/SDL-1.2.15/include/ 
LIBS= `sdl-config --libs` -lglew -lsdl_ttf -lpng -lsdl_image -framework opengl
OUTPUT=akari

PACKERSRC=../packer/main.cpp ../packer/pngfuncs.c
PACKEROUTPUT=pack


akari:
	$(CXX) $(FLAGS) $(SRC) $(INC) $(LIBS) -o $(OUTPUT)

packer:
	$(CXX) $(FLAGS) $(PACKERSRC) $(INC) $(LIBS) -o $(PACKEROUTPUT)

mm:
	$(CXX) $(FLAGS) -MM $(SRC) $(INC)

clean:
	rm $(OUTPUT)
	rm $(PACKEROUTPUT)
