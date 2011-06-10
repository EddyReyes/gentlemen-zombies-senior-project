#include "key.h"

key::key(void)
{
	type = stuff_key;
	m_object = NULL;
}

key::~key(void)
{
	//destruction of object is not handled by stuff class
}

void key::update(float updateTime)
{

}

void key::animate()
{
	m_object->setSprite(0,0);
}