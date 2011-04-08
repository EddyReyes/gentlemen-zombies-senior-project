#include "collisionRect.h"

collisionRect::collisionRect()//defualt constructor
{
	rect.bottom = NULL;
	rect.top = NULL;
	rect.left = NULL;
	rect.right = NULL;

}
int collisionRect::collided(FloatRect* a_rect)
{
	if(rect.bottom < a_rect->top) return 1;
	if(rect.top > a_rect->bottom) return 1;
	if(rect.right < a_rect->left) return 1;
	if(rect.left > a_rect->right) return 1;

	return 0;
}
//takes in an XYPlane and sets the rect based off of it
void collisionRect::setRect(XYPlane* object)
{
	rect.top =  object->getYPosition();
	rect.left = object->getXPosition();
	rect.right = object->getXPosition()+object->getWidth();
	rect.bottom = object->getYPosition()+object->getHeight();
}
// offsets the collision rectangle to fit smaller constraints
void collisionRect::setOffset(float x_offset, float y_offset)
{
	rect.top -= y_offset;
	rect.bottom += y_offset;
	rect.left += x_offset;
	rect.right -= x_offset;
}
//  more specific offset
void collisionRect::setOffset(float left, float right, float top, float bottom)
{
	rect.top -= top;
	rect.bottom += bottom;
	rect.left += left;
	rect.right -= right;
}
void collisionRect::setOffset(float offsetPercentage)
{
	rect.top -= this->getHeight() * offsetPercentage;
	rect.bottom += this->getHeight() * offsetPercentage;
	rect.left += this->getWidth() * offsetPercentage;
	rect.right -= this->getWidth() * offsetPercentage;
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
collisionRect::~collisionRect(){}
