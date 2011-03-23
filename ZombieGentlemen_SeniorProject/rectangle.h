#pragma once
#include "dxManager.h"
//#include <string>
struct XY{int x, y;};
struct size{int width, height;};

class rectangle
{
private: 
	IDirect3DSurface9* image; // sprite image
	RECT spriteSource;	// sprite section
	RECT onScreen; // sprite on screen
	XY rectLocation; // location of sprite
	int numSprites; // number of sprites in image
	dxManager * dxMgr;
	D3DXIMAGE_INFO imageInfo;

public:
	// defualt constructor
	rectangle();
	// constructors
	rectangle(dxManager * a_dxMgr, std::string filename, D3DCOLOR a_ColorKey);
	rectangle(dxManager * a_dxMgr, std::string filename, int a_numSprites, D3DCOLOR a_ColorKey);
	// destructor
	~rectangle();
	// initialize sprite variables
	void initRectangle();
	// set image of sprite
	void setImage(std::string filename);
	void setImage(std::string filename, int a_width, int a_height);
	void setImageWithColorKey(std::string filename, D3DCOLOR  a_ColorKey);
	void setImageWithColorKey(std::string filename, D3DCOLOR  a_ColorKey, int a_width, int a_height);
	void setNumSprites(int a_numSprites);
	// guess number of sprites based on file dimensions
	void guessNumSprites();
	// set source of sprite from image
	void setSpriteSource(RECT a_spriteSource);
	// set location of sprite
	void setLocation(XY a_Loc);
	// set location of sprite
	void setLocation(int a_x, int a_y);
	// set the size of onScreen
	void setSize(int a_width, int a_length);
	// set the size of onScreen
	void setSize(RECT newSize);
	// select a sprite (a portion of the image to show)
	void selectSpriteSource(int spriteIndex);
	// get sprite source pointer
	RECT * getSpriteSource();
	// get rectangle on screen
	RECT * getSpriteScreen();
	// draw sprite in its location
	void draw();
};