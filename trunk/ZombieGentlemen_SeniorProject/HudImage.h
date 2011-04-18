#pragma once
#include "dxManager.h"

class HudImage
{
private:
	dxManager * dxMgr;
	LPDIRECT3DTEXTURE9 image;	// image to hold sprite
	LPD3DXSPRITE sprite;		// sprite
	D3DXVECTOR3 position;		// position
	D3DXIMAGE_INFO * imageInfo;	// contains image parameters
	RECT spriteSource;	// sprite section
	D3DXMATRIX transform;
	int spriteColumns;
	int spriteRows;
	bool spriteOn;
	bool sharingImage;
	float xScale, yScale;

	// private member functions
	void initializeSprite(std::string filename);
	void initializeSprite();
	void guessSpriteColumns();	
	void initTrasform();
	void SetTransform();
	void scale();
	void normalizeCoordinates();

public:
	// constructors
	HudImage();
	HudImage(dxManager * a_dxMgr, std::string filename);
	HudImage(dxManager * a_dxMgr, LPDIRECT3DTEXTURE9 * a_image, D3DXIMAGE_INFO * a_imageInfo);
	
	// destructors
	~HudImage();
	void releaseImage();
	
	// member functions
	void draw();

	// mutators
	void setPosition(float a_x, float a_y);
	void setImage(std::string filename);
	void shareImage(LPDIRECT3DTEXTURE9 * a_image, D3DXIMAGE_INFO * a_imageInfo);
	void setSpriteColumns(int a_spriteColumns);
	void setSpriteRows(int a_spriteRows);
	void setRowsColumns(int a_spriteRows, int a_spriteColumns);
	void selectSpriteSource(int spriteIndex);
	void selectSpriteSource(int a_spriteRow, int a_spriteColumn);
	LPDIRECT3DTEXTURE9 * getTexture();
	D3DXIMAGE_INFO * getImageInfo();
	void toggleSprite();
	void setSize(float a_width, float a_height);
	void setParameters(float a_width, float a_height, float a_x, float a_y);
	
	// accessors
	float getHeight();
	float getWidth();
	float getXPosition();
	float getYPosition();
	float getNormalizedXPosition();
	float getNormalizedYPosition();
	float getWidthScale();
	float getHeightScale();
};