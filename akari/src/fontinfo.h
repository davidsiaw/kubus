#ifndef FONTINFO_H
#define FONTINFO_H

#pragma pack(push, 1)
struct fontinfo
{
	unsigned int chr;
    float width;
    float height;
    float x1, y1;
    float x2, y2;
    float x3, y3;
    float x4, y4;
};
#pragma pack(pop)

#endif // FONTINFO_H
