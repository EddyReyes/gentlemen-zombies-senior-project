#pragma once

struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw;      // The untransformed, 3D position for the vertex
    float tu, tv;        // The vertex color
};
struct FloatRect
{
	float right, left, bottom, top;
};

struct spriteMovement{
	// holds the location of this sprite
	RECT srcRect;		
	// x and y position of sprite
	int posX;
	int posY;
	// x and y movement of sprite
	int moveX;
	int moveY;
};