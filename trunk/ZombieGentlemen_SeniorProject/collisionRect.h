#pragma once
#include "dxManager.h"
#include "CustomVertex.h"
#include "XYPlane.h"


// XY struct will be depreciated soon, please remove it from
// anywhere you are using it
struct XY{int x, y;};


class collisionRect
{
private: 
	FloatRect rect;
public:
	collisionRect();
	~collisionRect();
	int collided(FloatRect* a_rect);

	// mutators
	void setRect(XYPlane* object);
	void setOffset(float x_offset, float y_offset);
	void setOffset(float left, float right, float top, float bottom);
	void setOffset(float offsetPercentage);
	void modifyRect(float width, float height);
	
	// accessors
	float getXPosition();
	float getYPosition();
	float getWidth();
	float getHeight();
	//D3DXVECTOR2 getPosition();
	FloatRect * getRect();
};