#pragma once
#include "dxManager.h"

class HudImage
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
	int spriteColumns;
	int spriteRows;
	bool spriteOn;
	bool sharingImage;
	float m_scale, xScale, yScale;

public:
	HudImage();
	HudImage(dxManager * a_dxMgr, std::string filename);
	HudImage(dxManager * a_dxMgr, std::string filename, int a_spriteRows);
	HudImage(dxManager * a_dxMgr, std::string filename, int a_spriteRows, int a_spriteColumns);
	HudImage(dxManager * a_dxMgr, LPDIRECT3DTEXTURE9 * a_image, D3DXIMAGE_INFO * a_imageInfo);
	HudImage(dxManager * a_dxMgr, LPDIRECT3DTEXTURE9 * a_image, D3DXIMAGE_INFO * a_imageInfo, int a_spriteRows);
	HudImage(dxManager * a_dxMgr, LPDIRECT3DTEXTURE9 * a_image, D3DXIMAGE_INFO * a_imageInfo, int a_spriteRows, int a_spriteColumns);
	~HudImage();
	void releaseImage();
	void initializeSprite(std::string filename);
	void initializeSprite();
	void draw();
	void drawCentered();
	void setPosition(int a_x, int a_y);
	void setPosition(int a_x, int a_y, int a_z);
	void setCenter(int a_x, int a_y);
	void setImage(std::string filename);
	void shareImage(LPDIRECT3DTEXTURE9 * a_image, D3DXIMAGE_INFO * a_imageInfo);
	void setSpriteColumns(int a_spriteColumns);
	void setSpriteRows(int a_spriteRows);
	void guessSpriteColumns();
	void selectSpriteSource(int spriteIndex);
	void selectSpriteSource(int a_spriteRow, int a_spriteColumn);
	LPDIRECT3DTEXTURE9 * getTexture();
	D3DXIMAGE_INFO * getImageInfo();
	void toggleSprite();
	void initTrasform();
	void scaleSize(float a_scale);
	void rotateSpriteY(float rotation);
	void rotateSpriteX(float rotation);
	void SetTransform();
	void setWidthScale(float widthScale);
	void setHeightScale(float heightScale);
	void scaleCustom();

	float getHeight();
	float getWidth();
	float getXPosition();
	float getYPosition();
	float getNormalizedXPosition();
	float getNormalizedYPosition();
	float getScale();
	float getWidthScale();
	float getHeightScale();
};