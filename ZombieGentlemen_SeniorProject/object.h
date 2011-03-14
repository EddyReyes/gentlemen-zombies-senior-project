#pragma once
/**
The object class is an abstract object that contains x,y information
as well ass virtual draw and update functions

will also hold image data

status: skeleton
*/
#include "dxManager.h"
struct XY{int x, y;};

class object
{
protected:
	XY location;
	int i;
	IDirect3DSurface9 * image;
	RECT src;
	RECT screen;
public:
	object(){};
};