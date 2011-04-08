#include "collisionRect.h"

collisionRect::collisionRect()//defualt constructor
{
	rect.bottom = NULL;
	rect.top = NULL;
	rect.left = NULL;
	rect.right = NULL;
	plane = NULL;
	cube = NULL;
	offSet.bottom = NULL;
	offSet.top = NULL;
	offSet.left = NULL;
	offSet.right = NULL;
}
int collisionRect::collided(FloatRect* a_rect)
{
	if(rect.bottom < a_rect->top) return 1;
	if(rect.top > a_rect->bottom) return 2;
	if(rect.left < a_rect->right) return 3;
	if(rect.right > a_rect->left) return 4;

	return 0;
}
//takes in an XYPlane and sets the rect based off of it
void collisionRect::initRect(XYPlane* a_plane)
{
	plane = a_plane;
	setRect();
}
void collisionRect::initRect(dxCube* a_cube)
{
	cube = a_cube;
	setRect();
}
void collisionRect::setRect()
{
	if(plane)
	{
		rect.top =  plane->getYPosition();
		rect.left = plane->getXPosition();
		rect.right = plane->getXPosition()+plane->getWidth();
		rect.bottom = plane->getYPosition()+plane->getHeight();
	}
	else if(cube)
	{
		rect.top =  cube->getYPosition();
		rect.left = cube->getXPosition();
		rect.right = cube->getXPosition()+cube->getWidth();
		rect.bottom = cube->getYPosition()+cube->getHeight();
	}
}
// offsets the collision rectangle to fit smaller constraints
void collisionRect::setOffset(FloatRect * a_offSet)
{
	offSet = *a_offSet;
}
void collisionRect::setOffset(float left, float right, float top, float bottom)
{
	offSet.left = left;
	offSet.right = right;
	offSet.top = top;
	offSet.bottom = bottom;
}
void collisionRect::offset()
{
	rect.top -= offSet.top;
	rect.bottom += offSet.bottom;
	rect.left += offSet.left;
	rect.right -= offSet.right;
}
//allows us to change the size of the rectangle at will
void collisionRect::modifyRect(float width, float height)
{
	rect.right = width;
	rect.bottom = height;
}
/**accessors**/
float collisionRect::getXPosition(){return rect.left;}
float collisionRect::getYPosition(){return rect.top;}
float collisionRect::getWidth(){return (rect.right - rect.left);}
float collisionRect::getHeight(){return (rect.bottom - rect.top);}
FloatRect * collisionRect::getRect(){return &rect;}
void collisionRect::update()
{
	setRect();
	offset();
}
collisionRect::~collisionRect(){}
