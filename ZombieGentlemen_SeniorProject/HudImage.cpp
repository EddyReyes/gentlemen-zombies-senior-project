#include "HudImage.h"

/*************************************************************************
* HudImage
* default constructor
*************************************************************************/
HudImage::HudImage(){};

/*************************************************************************
* HudImage
* constructors
* set up all the variables to a default value
* These constructors create a new image in memory for the passed in file
*************************************************************************/
HudImage::HudImage(dxManager * a_dxMgr, std::string filename)
{
	dxMgr = a_dxMgr;
	imageInfo = new D3DXIMAGE_INFO();
	initializeSprite(filename);
	spriteRows = 1;
	guessSpriteColumns();
	selectSpriteSource(0);
	initTrasform();
	spriteOn = true;
	sharingImage = false;
	m_scale = 1.0f;
	xScale = 1.0f;
	yScale = 1.0f;
}
HudImage::HudImage(dxManager * a_dxMgr, std::string filename, int a_spriteRows)
{
	dxMgr = a_dxMgr;
	imageInfo = new D3DXIMAGE_INFO();
	initializeSprite(filename);
	spriteRows = a_spriteRows;
	guessSpriteColumns();
	selectSpriteSource(0);
	initTrasform();
	spriteOn = true;
	sharingImage = false;
	m_scale = 1.0f;
	xScale = 1.0f;
	yScale = 1.0f;
}
HudImage::HudImage(dxManager * a_dxMgr, std::string filename, int a_spriteRows, int a_spriteColumns)
{
	dxMgr = a_dxMgr;
	imageInfo = new D3DXIMAGE_INFO();
	initializeSprite(filename);
	spriteRows = a_spriteRows;
	spriteColumns = a_spriteColumns;
	selectSpriteSource(0);
	initTrasform();
	spriteOn = true;
	sharingImage = false;
	m_scale = 1.0f;
	xScale = 1.0f;
	yScale = 1.0f;
}

/*************************************************************************
* HudImage
* constructors
* set up all the variables to a default value
* These constructors are for use when sharing an image with another object
*************************************************************************/
HudImage::HudImage(dxManager * a_dxMgr, LPDIRECT3DTEXTURE9 * a_image, D3DXIMAGE_INFO * a_imageInfo)
{
	dxMgr = a_dxMgr;
	image = *a_image;
	imageInfo = a_imageInfo;
	initializeSprite();
	spriteRows = 1;
	guessSpriteColumns();
	selectSpriteSource(0);
	initTrasform();
	spriteOn = true;
	sharingImage = true;
	m_scale = 1.0f;
	xScale = 1.0f;
	yScale = 1.0f;
}
HudImage::HudImage(dxManager * a_dxMgr, LPDIRECT3DTEXTURE9 * a_image, D3DXIMAGE_INFO * a_imageInfo, int a_spriteRows)
{
	dxMgr = a_dxMgr;
	image = *a_image;
	imageInfo = a_imageInfo;
	initializeSprite();
	spriteRows = a_spriteRows;
	guessSpriteColumns();
	selectSpriteSource(0);
	initTrasform();
	spriteOn = true;
	sharingImage = true;
	m_scale = 1.0f;
	xScale = 1.0f;
	yScale = 1.0f;
}
HudImage::HudImage(dxManager * a_dxMgr, LPDIRECT3DTEXTURE9 * a_image, D3DXIMAGE_INFO * a_imageInfo, int a_spriteRows, int a_spriteColumns)
{
	dxMgr = a_dxMgr;
	image = *a_image;
	imageInfo = a_imageInfo;
	initializeSprite();
	spriteRows = a_spriteRows;
	spriteColumns = a_spriteColumns;
	selectSpriteSource(0);
	initTrasform();
	spriteOn = true;
	sharingImage = true;
	m_scale = 1.0f;
	xScale = 1.0f;
	yScale = 1.0f;
}

/*************************************************************************
* ~HudImage
* destructor
* releases sprite structure from memory
* also releases image if it is not being shared
*************************************************************************/
HudImage::~HudImage()
{
	releaseImage();
	if( sprite != NULL )
	{
		sprite->Release();
		sprite = NULL;
	}
	if(imageInfo)
	{
		delete imageInfo;
		imageInfo = 0;
	}
	dxMgr = NULL;
}
/*************************************************************************
* releaseImage
* checks if image is being shared and then releases image if it is not
*************************************************************************/
void HudImage::releaseImage()
{
	if(!sharingImage)
	{
		if(image != NULL)
		{
			image->Release(); // release image if not being shared
			image = NULL;
		}
	}
}
/*************************************************************************
* initializeSprite
* initializes the sprite variables
* this version of the function also sets the image
*************************************************************************/
void HudImage::initializeSprite(std::string filename)
{
	D3DXCreateTextureFromFile(*dxMgr->getDevice(),filename.c_str(),&image);
	D3DXGetImageInfoFromFile(filename.c_str(), imageInfo);
	position.x=0.0f;
	position.y=0.0f;
	position.z=0.0f;
	center.x = position.x + imageInfo->Width/2;
	center.y = position.y + imageInfo->Height/2;
	center.z =0.0f;
	D3DXCreateSprite(*dxMgr->getDevice(),&sprite);
}
/*************************************************************************
* initializeSprite
* initializes the sprite variables
* this version of the function does not set the image
*************************************************************************/
void HudImage::initializeSprite()
{
	position.x=0.0f;
	position.y=0.0f;
	position.z=0.0f;
	center.x = position.x + imageInfo->Width/2;
	center.y = position.y + imageInfo->Height/2;
	center.z =0.0f;
	D3DXCreateSprite(*dxMgr->getDevice(),&sprite);
}
/*************************************************************************
* draw
* draws the sprite in its designated position on the condition that it is toggled as on
*************************************************************************/
void HudImage::draw()
{ 
	if(spriteOn)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DUSAGE_RENDERTARGET | D3DPOOL_DEFAULT);
		sprite->Draw(image,&spriteSource,NULL,&position,D3DCOLOR_XRGB(255,255,255));
		sprite->End();
	}
}
/*************************************************************************
* drawCentered
* draws the sprite in its designated position on the condition that it is toggled as on
* this version draws the sprite in accordance witht he center
* chances are this function will never be used but its here just in case
*************************************************************************/
void HudImage::drawCentered()
{
	if(spriteOn)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(image,&spriteSource,&center,&position,D3DCOLOR_XRGB(255,255,255));
		sprite->End();
	}
}
/*************************************************************************
* setPosition
* sets the position if the sprite in screen coordinates
*************************************************************************/
void HudImage::setPosition(int a_x, int a_y)
{
	position.x = (float)a_x;
	position.y = (float)a_y;
}
/*************************************************************************
* setCenter
* sets the center of the sprite
* chances are this function will never be needed
*************************************************************************/
void HudImage::setCenter(int a_x, int a_y)
{
	center.x = (float)a_x;
	center.y = (float)a_y;
}
/*************************************************************************
* setImage
* sets the image of the sprite and updates the files information
*************************************************************************/
void HudImage::setImage(std::string filename)
{
	D3DXCreateTextureFromFile(*dxMgr->getDevice(),filename.c_str(),&image);
	D3DXGetImageInfoFromFile(filename.c_str(), imageInfo);
	sharingImage = false;
}
/*************************************************************************
* shareImage
* sets the image of the sprite and updates the files information
*************************************************************************/
void HudImage::shareImage(LPDIRECT3DTEXTURE9 * a_image, D3DXIMAGE_INFO * a_imageInfo)
{
	releaseImage();
	image = *a_image;
	imageInfo = a_imageInfo;
	sharingImage = true;
}
/*************************************************************************
* setSpriteColumns
* sets the number of collumns within the sprite sheet
*************************************************************************/
void HudImage::setSpriteColumns(int a_spriteColumns){spriteColumns = a_spriteColumns;}

/*************************************************************************
* setSpriteRows
* sets the number of rows within the sprite sheet
*************************************************************************/
void HudImage::setSpriteRows(int a_spriteRows){spriteRows = a_spriteRows;}

/*************************************************************************
* guessSpriteColumns
* estimates the number of collumns in the situation where the sprite sheet is wider
* than it is tall
*************************************************************************/
void HudImage::guessSpriteColumns(){spriteColumns = imageInfo->Width/imageInfo->Height;}

/*************************************************************************
* selectSpriteSource
* sets the spriteSource RECT structure to the positon of any indididual sprite within the sprie sheet
*************************************************************************/
void HudImage::selectSpriteSource(int spriteIndex)
{
	spriteSource.top = 0;
	spriteSource.bottom = imageInfo->Height/spriteRows;
	spriteSource.left = spriteIndex * (imageInfo->Width/spriteColumns);
	spriteSource.right =  (spriteIndex * (imageInfo->Width/spriteColumns)) + (imageInfo->Width/spriteColumns);
}

/*************************************************************************
* selectSpriteSource
* sets the spriteSource RECT structure to the positon of any indididual sprite within the sprie sheet
* for use with sprires with more than one row
*************************************************************************/
void HudImage::selectSpriteSource(int a_spriteRow, int a_spriteColumn)
{
	spriteSource.top = (imageInfo->Height/spriteRows) * a_spriteRow;
	spriteSource.bottom = spriteSource.top + imageInfo->Height/spriteRows;
	spriteSource.left = a_spriteColumn * (imageInfo->Width/spriteColumns);
	spriteSource.right =  (a_spriteColumn * (imageInfo->Width/spriteColumns)) + (imageInfo->Width/spriteColumns);
}

/*************************************************************************
* getTexture
* accessor for the texture file
*************************************************************************/
LPDIRECT3DTEXTURE9 * HudImage::getTexture(){return &image;}
/*************************************************************************
* getImageInfo
* accessor for the image information
*************************************************************************/
D3DXIMAGE_INFO * HudImage::getImageInfo(){return imageInfo;}
/*************************************************************************
* toggleSprite
* toggles weather the sprite is on or off
* if the sprite is on it draws, if not it wont display when the draw function is called
*************************************************************************/
void HudImage::toggleSprite(){spriteOn = (spriteOn?false:true);}

/*************************************************************************
* initTrasform
* initialized the transform of the sprite
* this function is always called within the initializers
*************************************************************************/
void HudImage::initTrasform()
{
	sprite->GetTransform(&transform);
}

/*************************************************************************
* scaleSize
* uses matrix math to scale the sprite
*************************************************************************/
void HudImage::scaleSize(float a_scale)
{ 
	m_scale = a_scale;
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, m_scale, m_scale, m_scale);
	D3DXMatrixMultiply(&transform, &transform, &scale);
	sprite->SetTransform(&transform);
}
void HudImage::scaleCustom(float a_scale)
{ 
	m_scale = a_scale;
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, xScale, yScale, m_scale);
	D3DXMatrixMultiply(&transform, &transform, &scale);
	sprite->SetTransform(&transform);
}
/*************************************************************************
* rotateSpriteY
* meant to facilitate rotation around the Y axis, but it appears it wont be possible
* however rotation about the Z axis might be possible
*************************************************************************/
void HudImage::rotateSpriteY(float rotation)
{
	D3DXMATRIX rotate;
	D3DXMatrixRotationY(&rotate, rotation);
	D3DXMatrixMultiply(&transform, &transform, &rotate);  
}
void HudImage::rotateSpriteX(float rotation)
{
	D3DXMATRIX rotate;
	D3DXMatrixRotationX(&rotate, rotation);
	D3DXMatrixMultiply(&transform, &transform, &rotate);  
}
void HudImage::SetTransform()
{
	sprite->SetTransform(&transform);
}
void HudImage::setWidthScale(float widthScale)
{
	xScale = widthScale;
}
void HudImage::setHeightScale(float heightScale)
{
	yScale = heightScale;
}
/*************************************************************************
* getHeight, getWidth, getXPosition, getYPosition, getScale
* accesors: return the HudImage parameters
*************************************************************************/
float HudImage::getHeight(){return (imageInfo->Height * m_scale);}
float HudImage::getWidth(){return (imageInfo->Width * m_scale);}
float HudImage::getXPosition(){return position.x;}
float HudImage::getYPosition(){return position.y;}
float HudImage::getScale(){return m_scale;}
float HudImage::getWidthScale(){return xScale;}
float HudImage::getHeightScale(){return yScale;}
