SDLDIR=sdl
JPGDIR=jpeg
ZLIBDIR=zlib
PNGDIR=libpng
SDLIMGDIR=sdl_image
FTDIR=freetype
SDLTTFDIR=sdl_ttf
GLEWDIR=glew
LUADIR=lua
TOPDIR=`pwd`/..

all:
	cd $(SDLDIR); sh autogen.sh; ./configure --enable-video-x11-xme=no --prefix=$(TOPDIR)/build --enable-shared=no; make; make install
	# cd $(JPGDIR); ./configure --prefix=$(TOPDIR)/build; make; make install
	cd $(ZLIBDIR); ./configure --prefix=$(TOPDIR)/build --static; make; make install
	cd $(PNGDIR); CFLAGS=-I"$(TOPDIR)/$(ZLIBDIR)" LDFLAGS=-L"$(TOPDIR)/$(ZLIBDIR)" ./configure --prefix=$(TOPDIR)/build --enable-shared=no; make; make install
	cd $(SDLIMGDIR); sh autogen.sh; CPPFLAGS=-I"$(TOPDIR)/build/include" LDFLAGS=-L"$(TOPDIR)/build/lib" ./configure --prefix=$(TOPDIR)/build --enable-shared=no --enable-png-shared=no --with-sdl-prefix=$(TOPDIR)/build ; make; make install
	cd $(FTDIR); ./configure --prefix=$(TOPDIR)/build --enable-shared=no; make; make install
	cd $(SDLTTFDIR); sh autogen.sh; ./configure --with-freetype-prefix=$(TOPDIR)/build --prefix=$(TOPDIR)/build --enable-shared=no; make; make install
	cd $(GLEWDIR); make
	cp $(GLEWDIR)/lib/*.a build/lib/
	mkdir build/include/GL
	cp $(GLEWDIR)/include/GL/*.h build/include/GL

clean:
	cd $(SDLDIR); make distclean
	#cd $(JPGDIR); make clean
	cd $(ZLIBDIR); make distclean
	cd $(PNGDIR); make distclean
	cd $(SDLIMGDIR); make distclean
	cd $(FTDIR); make distclean
	cd $(SDLTTFDIR); make distclean
	cd $(GLEWDIR); make clean
	rm -rf build
	#cd $(LUADIR); make distclean
	

