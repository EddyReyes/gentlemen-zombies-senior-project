#pragma once
#include "dxManager.h"
//#include <string>
struct XY{int x, y;};
struct size{int width, height;};

class Sprite
{
private: 
	IDirect3DSurface9* image; // sprite image
	RECT spriteSource;	// sprite section
	RECT onScreen; // sprite on screen
	RECT newSpriteSource; // holds temporary sprite source, while out of bounds
	size spriteSize; // size of sprite
	size screenSize; // size of game screen
	size ImageSize; // size of overall image
	XY rectLocation; // location of sprite
	XY screenLocation; // location of game screen
	int numSprites; // number of sprites in image
	dxManager * dxMgr;
public:
	// defualt constructor
	Sprite(){};
	Sprite(dxManager * a_dxMgr)
	{
		dxMgr = a_dxMgr;
	}
	// constructor
	Sprite(dxManager * a_dxMgr, std::string filename, int a_width, int a_height)
	{
		dxMgr = a_dxMgr;
		ImageSize.height = a_height;
		ImageSize.width = a_width;
		setImage(filename);
	}
	// initialize sprite variables
	void initSprite(int a_numSprites, int a_screenWidth, int a_screenHeight)
	{
		numSprites = a_numSprites;
		spriteSize.height = ImageSize.height;
		spriteSize.width = ImageSize.width/numSprites;
		selectSpriteSource(0);
		onScreen = spriteSource;
		screenSize.height = a_screenHeight;
		screenSize.width = a_screenWidth;
		setLocation(0,0);
		setScreenLocation(0,0);
	}
	// destructor
	~Sprite(){};
	// set image of sprite
	void setImage(std::string filename)
	{
		image = dxMgr->getSurfaceFromBitmap(filename,ImageSize.width, ImageSize.height);
	}
	void setImage(std::string filename, int a_width, int a_height)
	{
		image = dxMgr->getSurfaceFromBitmap(filename,a_width, a_height);
	}
	void setNumSprites(int a_numSprites)
	{
		numSprites = a_numSprites;
		spriteSize.height = ImageSize.height/numSprites;
		spriteSize.width = ImageSize.width/numSprites;
	}
	// set size of sprite
	void setSpriteSize(int a_width, int a_height)
	{
		spriteSize.height = a_height;
		spriteSize.width = a_width;
	}
	// set source of sprite from image
	void setSpriteSource(RECT a_spriteSource)
	{
		spriteSource.top = a_spriteSource.top;
		spriteSource.bottom = a_spriteSource.bottom;
		spriteSource.left = a_spriteSource.left;
		spriteSource.right = a_spriteSource.right;
	}
	// set game screen size
	void setScreenSize(int a_width, int a_height)
	{
		screenSize.height = a_height;
		screenSize.width = a_width;
	}
	// set size of overall image
	void setImageSize(int a_width, int a_height)
	{
		ImageSize.height = a_height;
		ImageSize.width = a_width;
	}
	// set location of sprite
	void setLocation(XY a_Loc)
	{
		rectLocation.x = a_Loc.x;
		rectLocation.y = a_Loc.y;
	}
	// set location of sprite
	void setLocation(int a_x, int a_y)
	{
		rectLocation.x = a_x;
		rectLocation.y = a_y;
	}
	// set location of game screen
	void setScreenLocation(XY a_ScreenLoc)
	{
		screenLocation.x = a_ScreenLoc.x;
		screenLocation.y = a_ScreenLoc.y;
	}
	// set location of game screen
	void setScreenLocation(int a_x, int a_y)
	{
		screenLocation.x = a_x;
		screenLocation.y = a_y;
	}
	// select a sprite (a portion of the image to show)
	void selectSpriteSource(int spriteIndex)
	{
		spriteSource.top = 0;
		spriteSource.bottom = ImageSize.height;
		spriteSource.left = spriteIndex * spriteSize.width;
		spriteSource.right =  (spriteIndex * spriteSize.width) + spriteSize.width;
	}
	// fill newsprite data
	void fillNewSprite()
	{
		// initialize newSprite
		newSpriteSource = spriteSource;
		onScreen.left = rectLocation.x;
		onScreen.right = rectLocation.x + spriteSize.width;
		onScreen.top = rectLocation.y;
		onScreen.bottom = rectLocation.y + spriteSize.height;
	}

	// update newsprite data based on the position of the sprite
	void updateRect()
	{
		fillNewSprite();
		// check if rectLocation is within screenLocation	
		// check if rectLocation.x is out of bounds
		if (rectLocation.x < screenLocation.x)
		{
			// adjustSpriteSource to acommodate rectangle within the screen	
			newSpriteSource.left += screenLocation.x - rectLocation.x;
			onScreen.left = 0;
			onScreen.right -= screenLocation.x - rectLocation.x;
		}
		// check if rectLocation + spriteSize.width is within screenLocation
		if(rectLocation.x + spriteSize.width > screenLocation.x + screenSize.width)
		{
			// adjustSpriteSource to acommodate rectangle within the screen
			newSpriteSource.right -= rectLocation.x - screenLocation.x;
			onScreen.right = screenSize.width;
		}

		// check if rectLocation.y is within screenLocation
		if(rectLocation.y < screenLocation.y)
		{
			// adjustSpriteSource to acommodate rectangle within the screen
			newSpriteSource.top += screenLocation.y - rectLocation.y;
			onScreen.top = 0;
			onScreen.bottom -= screenLocation.y - rectLocation.y;
		}
					
		// check if rectLocation + spriteSize.height is out of bounds
		if(rectLocation.y + spriteSize.height > screenLocation.y + screenSize.height)
		{
			// adjustSpriteSource to acommodate rectangle within the screen
			newSpriteSource.bottom -= rectLocation.y - screenLocation.y;
			onScreen.bottom = screenSize.height;
		}	
	}
	// get sprite source pointer
	RECT * getSpriteSource(){return &newSpriteSource;}
	// get rectangle on screen
	RECT * getSpriteScreen(){return &onScreen;}
	// draw sprite in its location
	void draw()
	{
		dxMgr->blitToSurface(image, &newSpriteSource, &onScreen);
	}
};