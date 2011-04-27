#pragma once
#include "dxManager.h"
#include "CustomVertex.h"
#include "XYPlane.h"
#include "dxCube.h"


// XY struct will be depreciated soon, please remove it from
// anywhere you are using it
struct XY{int x, y;};
//used for collision classification
#define COL_LEFT (1)
#define COL_RIGHT (1<<1)
#define COL_TOP (1<<2)
#define COL_BOT (1<<3)

class collisionRect
{
private: 
	FloatRect rect;
	FloatRect offSet;
	XYPlane * plane;
	dxCube * cube;
public:
	collisionRect();
	~collisionRect();
	bool collided(FloatRect* a_rect);

	// mutators
	void initRect(XYPlane* plane);
	void initRect(dxCube* cube);
	void setRect();
	void setOffset(FloatRect * a_offSet);
	void setOffset(float left, float right, float top, float bottom);
	void offset();
	void modifyParameters(float a_x, float a_y, float width, float height);
	void update();
	
	// accessors
	float getXPosition();
	float getYPosition();
	float getWidth();
	float getHeight();
	//D3DXVECTOR2 getPosition();
	FloatRect * getRect();

	int classify(FloatRect* a_rect);
};