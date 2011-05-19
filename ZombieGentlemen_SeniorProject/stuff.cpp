#include "stuff.h"

stuff::stuff(void)
{
	m_object = NULL;
	type = stuff_none;
	pickedUp = false;
}

stuff::~stuff(void)
{
	// stuff does not create or destroy objects
}

void stuff::setPosition(float x, float y)
{
	m_object->setPosition(x, y, 0);
	m_object->recordPosition();
}
void stuff::pickUp(){pickedUp = true;}

bool stuff::isPickedUp()
{
	return pickedUp;
}
void stuff::setObject(object * a_object)
{
	m_object = a_object;
}
object * stuff::getObject()
{
	return m_object;;
}
int stuff::getType(){return type;}