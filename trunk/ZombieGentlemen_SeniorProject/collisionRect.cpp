#include "collisionRect.h"

collisionRect::collisionRect()//defualt constructor
{
	rect.bottom = NULL;
	rect.top = NULL;
	rect.left = NULL;
	rect.right = NULL;

}
//takes in an XYPlane and sets the rect based off of it
void collisionRect::SetcollisionRect(XYPlane* object)
{
	rect.top =  object->getYPosition();
	rect.left = object->getXPosition();
	rect.right = object->getXPosition()+object->getWidth();
	rect.bottom = object->getYPosition()+object->getHeight();
}
int collisionRect::collided(collisionRect* a_rect)//stub
{
	float left2, right2, top2, bottom2;
	left2 = a_rect->getRect().left;
	right2 = a_rect->getRect().right;
	top2 = a_rect->getRect().top;
	bottom2 = a_rect->getRect().bottom;

	if(rect.right<left2||
		rect.left>right2||
		rect.top>bottom2||
		rect.bottom<top2)
		return 1;
	else
		return 0;
}
//allows us to change the size of the rectangle at will
void collisionRect::setRect(float width, float height)
{
	rect.right = width;
	rect.bottom = height;
}
//void collisionRect::setPosition(float a_x,float a_y)
//{
//	pos.x = a_x;
//	pos.y = a_y;
//}

/**accessors**/
float collisionRect::getXPosition()
{
	return rect.left;
}
float collisionRect::getYPosition()
{
	return rect.top;
}
float collisionRect::getWidth()
{
	return rect.right;
}
float collisionRect::getHeight()
{
	return rect.bottom;
}
//D3DXVECTOR2 collisionRect::getPosition()//stub
//{
//	return pos;
//}
FloatRect collisionRect::getRect()
{
	return rect;
}
collisionRect::~collisionRect()
{
}
