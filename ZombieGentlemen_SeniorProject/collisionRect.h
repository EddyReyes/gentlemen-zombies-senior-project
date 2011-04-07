#pragma once
#include "dxManager.h"
#include "CustomVertex.h"


// XY struct will be depreciated soon, please remove it from
// anywhere you are using it
struct XY{int x, y;};


class collisionRect
{
private: 
	FloatRect rect;
	D3DXVECTOR2 pos;
public:
	collisionRect();
	~collisionRect();
	int collided(collisionRect a_rect);

	// mutators
	void setRect(float width, float height);
	void setPosition(float a_x, float a_y);
	
	// accessors
	float getXPosition();
	float getYPosition();
	float getWidth();
	float getHeight();
	D3DXVECTOR2 getPosition();
	FloatRect getRect();
};