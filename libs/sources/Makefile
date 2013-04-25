SDLDIR=SDL-1.2.15
JPGDIR=jpeg-6b
ZLIBDIR=zlib-1.2.5
PNGDIR=libpng-1.5.5
SDLIMGDIR=SDL_image-1.2.10
FTDIR=freetype-2.1.10
SDLTTFDIR=SDL_ttf-2.0.10
GLEWDIR=glew-1.7.0
LUADIR=lua-5.2.0


all:
	cd $(SDLDIR); ./configure; make
	cd $(JPGDIR); make
	cd $(ZLIBDIR); make
	cd $(PNGDIR); ./configure; make
	cd $(SDLIMGDIR); ./configure; make
	cd $(FTDIR); ./configure; make
	cd $(SDLTTFDIR); ./configure; make
	cd $(GLEWDIR); make
	cd $(LUADIR); make macosx
	cp $(SDLDIR)/build/.libs/libSDL.a build/libs/
	cp $(SDLDIR)/build/.libs/libSDLmain.a build/libs/
	cp $(SDLIMGDIR)/.libs/libSDL_image.a build/libs/
	cp $(SDLTTFDIR)/.libs/libSDL_ttf.a build/libs/
	cp $(GLEWDIR)/lib/libGLEW.a build/libs/
	cp $(SDLDIR)/include build/include/SDL


clean:
	cd $(SDLDIR); make clean
	cd $(JPGDIR); make clean
	cd $(ZLIBDIR); make clean
	cd $(PNGDIR); make clean
	cd $(SDLIMGDIR); make clean
	cd $(FTDIR); make clean
	cd $(SDLTTFDIR); make clean
	cd $(GLEWDIR); make clean
	cd $(LUADIR); make clean
	

