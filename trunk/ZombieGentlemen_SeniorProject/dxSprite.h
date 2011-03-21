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
	D3DXIMAGE_INFO imageInfo;	// contains image parameters
	RECT spriteSource;	// sprite section
	D3DXMATRIX transform;
	int numSprites; // number of sprites in image

public:
	dxSprite(){};
	// constructor
	dxSprite(dxManager * a_dxMgr, std::string filename)
	{
		dxMgr = a_dxMgr;
		D3DXGetImageInfoFromFile(filename.c_str(), &imageInfo);
		initializeSprite(filename);
		guessNumSprites();
		selectSpriteSource(0);
		initTrasform();
	}

	dxSprite(dxManager * a_dxMgr, std::string filename, int a_numSprites)
	{
		dxMgr = a_dxMgr;
		D3DXGetImageInfoFromFile(filename.c_str(), &imageInfo);
		initializeSprite(filename);
		numSprites = a_numSprites;
		selectSpriteSource(0);
		initTrasform();
	}
	void initializeSprite(std::string filename)
	{
		D3DXCreateTextureFromFile(*dxMgr->getDevice(),filename.c_str(),&image);
		position.x=0.0f;
		position.y=0.0f;
		position.z=0.0f;
		center.x = position.x + imageInfo.Width/2;
		center.y = position.y + imageInfo.Height/2;
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
		D3DXGetImageInfoFromFile(filename.c_str(), &imageInfo);
	}
	void setNumSprites(int a_numSprites){numSprites = a_numSprites;}
	// guess number of sprites based on file dimensions
	void guessNumSprites(){numSprites = imageInfo.Width/imageInfo.Height;}
	
	void selectSpriteSource(int spriteIndex)
	{
		spriteSource.top = 0;
		spriteSource.bottom = imageInfo.Height;
		spriteSource.left = spriteIndex * (imageInfo.Width/numSprites);
		spriteSource.right =  (spriteIndex * (imageInfo.Width/numSprites)) + (imageInfo.Width/numSprites);
	}
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