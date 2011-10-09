#!/bin/bash

cd SDL-*
./configure --enable-static=yes --enable-shared=no
make
make install
cp include ../../
cp build/.libs/libSDL.a $x86
cd ..

cd zlib-*
./configure
make
make install
cp *.h ../../include/
cp libz.a $x86
cd ..

cd libpng*
./configure --enable-static=yes --enable-shared=no --with-zlib-prefix=$86
make
make install
cp *.h ../../include
cp .libs/libpng15.a $86/libpng.a
cd ..

cd jpeg-*
./configure --enable-static
make
make install
cp *.h ../../include
cp libjpeg.a $x86

cd SDL_image*
./configure --enable-static=yes

cd freetype*
