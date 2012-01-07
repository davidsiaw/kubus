#!/bin/bash

SDL_SRC="http://www.libsdl.org/release/SDL-1.2.14.tar.gz"
SDLIMAGE_SRC="http://www.libsdl.org/projects/SDL_image/release/SDL_image-1.2.10.tar.gz"
SDLTTF_SRC="http://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-2.0.10.tar.gz"
LIBPNG_SRC="http://prdownloads.sourceforge.net/libpng/libpng-1.5.5.tar.xz?download"
LIBZ_SRC="http://zlib.net/zlib-1.2.5.tar.gz"
LIBJPEG_SRC="http://downloads.sourceforge.net/project/libjpeg/libjpeg/6b/jpegsrc.v6b.tar.gz?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Flibjpeg%2Ffiles%2Flibjpeg%2F6b%2F&ts=1317540891&use_mirror=voxel"
LIBFREETYPE_SRC="http://download.savannah.gnu.org/releases/freetype/freetype-2.1.10.tar.bz2"
GLEW_SRC="http://downloads.sourceforge.net/project/glew/glew/1.7.0/glew-1.7.0.tgz?r=http%3A%2F%2Fglew.sourceforge.net%2F&ts=1317627466&use_mirror=superb-sea2"
LUA_SRC="http://www.lua.org/ftp/lua-5.2.0.tar.gz"

x86="../../x86/"

mkdir "libs/sources"
mkdir "libs/x86"
mkdir "libs/lib"

cd libs/sources
#wget $SDL_SRC
#wget $SDLIMAGE_SRC
#wget $SDLTTF_SRC
#wget $LIBPNG_SRC
#wget $LIBZ_SRC
#wget $LIBJPEG_SRC
wget $LIBFREETYPE_SRC
wget $GLEW_SRC
wget $LUA_SRC

tar xvf SDL-*.tar.gz
tar xvf SDL_image*.tar.gz
tar xvf SDL_ttf*.tar.gz
tar xvf libpng-*.tar.xz
tar xvf zlib-*.tar.xz
tar xvf jpeg*.tar.gz
tar xvf freetype*.tar.bz2
tar xvf glew*.tgz
tar xvf lua*.tgz
