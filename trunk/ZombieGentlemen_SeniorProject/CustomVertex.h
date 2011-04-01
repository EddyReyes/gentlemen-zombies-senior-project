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