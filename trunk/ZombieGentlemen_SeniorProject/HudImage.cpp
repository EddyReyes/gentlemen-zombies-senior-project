#include "HudImage.h"

/*************************************************************************
* HudImage
* default constructor
*************************************************************************/
HudImage::HudImage(){};

/*************************************************************************
* HudImage
* constructor
* set up all the variables to a default value
* This constructor creates a new image in memory for the passed in file
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
	xScale = 1.0f;
	yScale = 1.0f;
}
/*************************************************************************
* HudImage
* constructor
* set up all the variables to a default value
* This constructor is for use when sharing an image with another object
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
* setPosition
* sets the position if the sprite in screen coordinates
*************************************************************************/
void HudImage::setPosition(float a_x, float a_y)
{
	position.x = a_x;
	position.y = a_y;

}
void HudImage::normalizeCoordinates()
{
	if(xScale != 1.0f || yScale != 1.0f)
	{
		position.x *= 1/ xScale;
		position.y *= 1/ yScale;
	}
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
* setRowsColumns
* sets the number of rows and columns within the sprite sheet
*************************************************************************/
void HudImage::setRowsColumns(int a_spriteRows, int a_spriteColumns)
{
	spriteRows = a_spriteRows;
	spriteColumns = a_spriteColumns;
}

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
void HudImage::toggleSpriteOn(){spriteOn = true;}
void HudImage::toggleSpriteOff(){spriteOn = false;}

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
void HudImage::scale()
{ 
	float m_scale = 1.0f;
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, xScale, yScale, m_scale);
	D3DXMatrixMultiply(&transform, &transform, &scale);
	sprite->SetTransform(&transform);
}
void HudImage::setSize(float a_width, float a_height)
{
	xScale = (a_width/(float)imageInfo->Width/spriteColumns);
	yScale = (a_height/(float)imageInfo->Height/spriteRows);
	scale();
}
void HudImage::setParameters(float a_width, float a_height, float a_x, float a_y)
{
	setSize(a_width, a_height);
	setPosition(a_x, a_y);
	normalizeCoordinates();
}
void HudImage::SetTransform()
{
	sprite->SetTransform(&transform);
}
/*************************************************************************
* getHeight, getWidth, getXPosition, getYPosition, getScale
* accesors: return the HudImage parameters
*************************************************************************/
float HudImage::getHeight(){return (imageInfo->Height * yScale);}
float HudImage::getWidth(){return (imageInfo->Width * xScale);}
// getXPosition & getYPosition return the position in correct screen coordinates
float HudImage::getXPosition(){return position.x / (1/ xScale);}
float HudImage::getYPosition(){return position.y / (1/ yScale);}
// getNormalizedXPosition & getNormalizedYPosition return the true position
float HudImage::getNormalizedXPosition(){return position.x;}
float HudImage::getNormalizedYPosition(){return position.y;}
float HudImage::getWidthScale(){return xScale;}
float HudImage::getHeightScale(){return yScale;}
