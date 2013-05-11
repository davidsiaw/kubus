#ifndef CHARMAPINFO_H
#define CHARMAPINFO_H

struct charmapinformation {
	int numtiles;	// number of frames in this tile animation
	float xsize;	// size of each tile horizontally
	float ysize;	// size of each tile vertically
	float xstart;	// left position in the tile
	float ystart;	// bottom position in the tile
	int xoffset;	// offset of the tile relative to the terrain
	int yoffset;
	int xpixsize;
	int ypixsize;
};

#endif //CHARMAPINFO_H
