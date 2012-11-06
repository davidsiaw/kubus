#ifndef TILEINFO_H
#define TILEINFO_H

#pragma pack(push, 1)
struct tileinfo
{
	int numframes;
	float width;
	float height;

	//texcoords
	float x1, y1;
	float x2, y2;
	float x3, y3;
	float x4, y4;
};
#pragma pack(pop)

#endif // TILEINFO_H
