CXX=clang++
FLAGS=-g -std=c++11 -stdlib=libc++
SRC=`ls ../src/*.cpp`
INC=-I ../src/ -I ../../libs/sources/boost_1_53_0/ -I ../../libs/sources/SDL_image-1.2.10/ -I ../../libs/sources/SDL_ttf-2.0.10/ -I ../../libs/sources/SDL-1.2.15/include/ 
LIBS= `sdl-config --libs` -lglew -lsdl_ttf -lsdl_image -framework opengl
OUTPUT=-o akari

all:
	$(CXX) $(FLAGS) $(SRC) $(INC) $(LIBS) $(OUTPUT)


clean:

