#pragma once
#include "dxManager.h"

class dxSprite
{
private:
	dxManager * dxMgr;
	LPDIRECT3DTEXTURE9 image;	// image to hold sprite
	LPD3DXSPRITE sprite;		// sprite
	D3DXVECTOR3 position;		// position
	D3DXVECTOR3 center;			// center
	D3DXIMAGE_INFO * imageInfo;	// contains image parameters
	RECT spriteSource;	// sprite section
	D3DXMATRIX transform;
	//int numSprites; // number of sprites in image
	int spriteColumns;
	int spriteRows;

public:
	dxSprite(){};
	// constructor
	dxSprite(dxManager * a_dxMgr, std::string filename)
	{
		dxMgr = a_dxMgr;
		imageInfo = new D3DXIMAGE_INFO();
		D3DXGetImageInfoFromFile(filename.c_str(), imageInfo);
		initializeSprite(filename);
		spriteRows = 1;
		guessSpriteColumns();
		selectSpriteSource(0);
		initTrasform();
	}
	dxSprite(dxManager * a_dxMgr, std::string filename, int a_spriteRows)
	{
		dxMgr = a_dxMgr;
		imageInfo = new D3DXIMAGE_INFO();
		D3DXGetImageInfoFromFile(filename.c_str(), imageInfo);
		initializeSprite(filename);
		spriteRows = a_spriteRows;
		guessSpriteColumns();
		selectSpriteSource(0);
		initTrasform();
	}
	dxSprite(dxManager * a_dxMgr, std::string filename, int a_spriteRows, int a_spriteColumns)
	{
		dxMgr = a_dxMgr;
		imageInfo = new D3DXIMAGE_INFO();
		D3DXGetImageInfoFromFile(filename.c_str(), imageInfo);
		initializeSprite(filename);
		spriteRows = a_spriteRows;
		spriteColumns = a_spriteColumns;
		selectSpriteSource(0);
		initTrasform();
	}

	dxSprite(dxManager * a_dxMgr, LPDIRECT3DTEXTURE9 * a_image, D3DXIMAGE_INFO * a_imageInfo)
	{
		dxMgr = a_dxMgr;
		image = *a_image;
		imageInfo = a_imageInfo;
		initializeSprite();
		spriteRows = 1;
		guessSpriteColumns();
		selectSpriteSource(0);
		initTrasform();
	}
	dxSprite(dxManager * a_dxMgr, LPDIRECT3DTEXTURE9 * a_image, D3DXIMAGE_INFO * a_imageInfo, int a_spriteRows)
	{
		dxMgr = a_dxMgr;
		image = *a_image;
		imageInfo = a_imageInfo;
		initializeSprite();
		spriteRows = a_spriteRows;
		guessSpriteColumns();
		selectSpriteSource(0);
		initTrasform();
	}
	dxSprite(dxManager * a_dxMgr, LPDIRECT3DTEXTURE9 * a_image, D3DXIMAGE_INFO * a_imageInfo, int a_spriteRows, int a_spriteColumns)
	{
		dxMgr = a_dxMgr;
		image = *a_image;
		imageInfo = a_imageInfo;
		initializeSprite();
		spriteRows = a_spriteRows;
		spriteColumns = a_spriteColumns;
		selectSpriteSource(0);
		initTrasform();
	}

	~dxSprite()
	{
		if( sprite != NULL )
			sprite->Release();
	}
	void releaseImage()
	{if( image != NULL )
			image->Release();
	}
	void initializeSprite(std::string filename)
	{
		D3DXCreateTextureFromFile(*dxMgr->getDevice(),filename.c_str(),&image);
		position.x=0.0f;
		position.y=0.0f;
		position.z=0.0f;
		center.x = position.x + imageInfo->Width/2;
		center.y = position.y + imageInfo->Height/2;
		center.z =0.0f;
		D3DXCreateSprite(*dxMgr->getDevice(),&sprite);
	}
	void initializeSprite()
	{
		position.x=0.0f;
		position.y=0.0f;
		position.z=0.0f;
		center.x = position.x + imageInfo->Width/2;
		center.y = position.y + imageInfo->Height/2;
		center.z =0.0f;
		D3DXCreateSprite(*dxMgr->getDevice(),&sprite);
	}
	void drawSprite()
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(image,&spriteSource,NULL,&position,D3DCOLOR_XRGB(255,255,255));
		sprite->End();
	}
	void drawCenteredSprite()
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(image,&spriteSource,&center,&position,D3DCOLOR_XRGB(255,255,255));
		sprite->End();
	}
	void setPosition(int a_x, int a_y)
	{
		position.x = (float)a_x;
		position.y = (float)a_y;
	}
	void setCenter(int a_x, int a_y)
	{
		center.x = (float)a_x;
		center.y = (float)a_y;
	}
	void setImage(std::string filename)
	{
		D3DXCreateTextureFromFile(*dxMgr->getDevice(),filename.c_str(),&image);
		D3DXGetImageInfoFromFile(filename.c_str(), imageInfo);
	}
	// set spriteColumns
	void setSpriteColumns(int a_spriteColumns){spriteColumns = a_spriteColumns;}
	// set spriteRows
	void setSpriteRows(int a_spriteRows){spriteRows = a_spriteRows;}
	// guess number of spriteColumns based on file dimensions
	void guessSpriteColumns(){spriteColumns = imageInfo->Width/imageInfo->Height;}
	
	// for use with sprites with only one row
	void selectSpriteSource(int spriteIndex)
	{
		spriteSource.top = 0;
		spriteSource.bottom = imageInfo->Height/spriteRows;
		spriteSource.left = spriteIndex * (imageInfo->Width/spriteColumns);
		spriteSource.right =  (spriteIndex * (imageInfo->Width/spriteColumns)) + (imageInfo->Width/spriteColumns);
	}
	// for use with sprites with more than one row
	void selectSpriteSource(int a_spriteRow, int a_spriteColumn)
	{
		spriteSource.top = imageInfo->Height * a_spriteRow;
		spriteSource.bottom = spriteSource.top + imageInfo->Height/spriteRows;
		spriteSource.left = a_spriteColumn * (imageInfo->Width/spriteColumns);
		spriteSource.right =  (a_spriteColumn * (imageInfo->Width/spriteColumns)) + (imageInfo->Width/spriteColumns);
	}

	LPDIRECT3DTEXTURE9 * getTexture(){return &image;}
	D3DXIMAGE_INFO * getImageInfo(){return imageInfo;}


	void initTrasform()
	{
		sprite->GetTransform(&transform);
	}

	void scaleSize(float a_scale)
	{
		D3DXMATRIX scale;
		D3DXMatrixScaling(&scale, a_scale, a_scale, a_scale);
		D3DXMatrixMultiply(&transform, &transform, &scale);
		sprite->SetTransform(&transform);
	}

	// these functions still need work
	void rotateSpriteY(float rotation)
	{
		D3DXMATRIX rotate;
		D3DXMatrixRotationY(&rotate, rotation);
		D3DXMatrixMultiply(&transform, &transform, &rotate);  
	}
	void rotateSpriteX(float rotation)
	{
		D3DXMATRIX rotate;
		D3DXMatrixRotationX(&rotate, rotation);
		D3DXMatrixMultiply(&transform, &transform, &rotate);  
	}
	void SetTransform()
	{
		sprite->SetTransform(&transform);
	}
};