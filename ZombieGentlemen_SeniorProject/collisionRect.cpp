#include "collisionRect.h"

collisionRect::collisionRect()
{
	rect.bottom = NULL;
	rect.top = NULL;
	rect.left = NULL;
	rect.right = NULL;

	pos.x = 0;
	pos.y = 0;

}
int collisionRect::collided(collisionRect* a_rect)//stub
{
	return 0;
}
void collisionRect::setRect(float width, float height)//stub
{
}
void collisionRect::setPosition(float a_x,float a_y)//stub
{
}
float collisionRect::getXPosition()//stub
{
	return 0;
}
float collisionRect::getYPosition()//stub
{
	return 0;
}
float collisionRect::getWidth()//stub
{
	return 0;
}
float collisionRect::getHeight()//stub
{
	return 0;
}
D3DXVECTOR2 collisionRect::getPosition()//stub
{
	return pos;
}
FloatRect collisionRect::getRect()//stub
{
	return rect;
}