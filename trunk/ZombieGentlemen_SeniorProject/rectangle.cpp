#include "rectangle.h"
// defualt constructor
rectangle::rectangle(){}
// constructor
rectangle::rectangle(dxManager * a_dxMgr, std::string filename)
{
	dxMgr = a_dxMgr;
	D3DXGetImageInfoFromFile(filename.c_str(), &imageInfo);
	setImage(filename);
	guessNumSprites();
	initRectangle();
}
rectangle::rectangle(dxManager * a_dxMgr, std::string filename, int a_numSprites)
{
	dxMgr = a_dxMgr;
	numSprites = a_numSprites;
	D3DXGetImageInfoFromFile(filename.c_str(), &imageInfo);
	setImage(filename);
	initRectangle();
}
// destructor
rectangle::~rectangle()
{
	image->Release();
}
// initialize sprite variables
void rectangle::initRectangle()
{
	selectSpriteSource(0);
	onScreen = spriteSource;
	setLocation(0,0);
}
// set image of sprite
void rectangle::setImage(std::string filename)
{
	image = dxMgr->getSurfaceFromBitmap(filename,imageInfo.Width, imageInfo.Height);
}
void rectangle::setImage(std::string filename, int a_width, int a_height)
{
	image = dxMgr->getSurfaceFromBitmap(filename,a_width, a_height);
}
void rectangle::setNumSprites(int a_numSprites)
{
	numSprites = a_numSprites;
}
// guess number of sprites based on file dimensions
void rectangle::guessNumSprites(){numSprites = imageInfo.Width/imageInfo.Height;}
// set source of sprite from image
void rectangle::setSpriteSource(RECT a_spriteSource)
{
	spriteSource.top = a_spriteSource.top;
	spriteSource.bottom = a_spriteSource.bottom;
	spriteSource.left = a_spriteSource.left;
	spriteSource.right = a_spriteSource.right;
}
// set location of sprite
void rectangle::setLocation(XY a_Loc)
{
	rectLocation.x = a_Loc.x;
	rectLocation.y = a_Loc.y;
}
// set location of sprite
void rectangle::setLocation(int a_x, int a_y)
{
	rectLocation.x = a_x;
	rectLocation.y = a_y;
}
	// set the size of onScreen
void rectangle::setSize(int a_width, int a_length)
{
	onScreen.top = 0 + rectLocation.y;
	onScreen.left = 0 + rectLocation.x;
	onScreen.right = a_width + rectLocation.x;
	onScreen.bottom = a_length + rectLocation.y;
}
	// set the size of onScreen
void rectangle::setSize(RECT newSize)
{
	onScreen.top = newSize.top;
	onScreen.left = newSize.left;
	onScreen.right = newSize.right;
	onScreen.bottom = newSize.bottom;
}
// select a sprite (a portion of the image to show)
void rectangle::selectSpriteSource(int spriteIndex)
{
	spriteSource.top = 0;
	spriteSource.bottom = imageInfo.Height;
	spriteSource.left = spriteIndex * (imageInfo.Width/numSprites);
	spriteSource.right =  (spriteIndex * (imageInfo.Width/numSprites)) + (imageInfo.Width/numSprites);
}
// get sprite source pointer
RECT * rectangle::getSpriteSource(){return &spriteSource;}
// get rectangle on screen
RECT * rectangle::getSpriteScreen(){return &onScreen;}
// draw sprite in its location
void rectangle::draw()
{
	dxMgr->blitToSurface(image, &spriteSource, &onScreen);
}