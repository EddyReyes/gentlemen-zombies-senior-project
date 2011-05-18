#include "stuff.h"

stuff::stuff(void)
{
	m_object = NULL;
	type = none;
	pickedUp = false;
}

stuff::~stuff(void)
{
}

void stuff::setPosition(float x, float y)
{

}
void stuff::crossed()
{
}
bool stuff::isCrossed()
{
	return NULL;
}
void stuff::setObject(object * a_object)
{
}
object * stuff::getObject()
{
	return NULL;
}