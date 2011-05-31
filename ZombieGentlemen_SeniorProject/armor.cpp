#include "armor.h"

armor::armor()
{
	type = stuff_armor;
	m_object = NULL;
}

armor::~armor(void)
{

}

void armor::update(float timePassed)
{

}

void armor::animate()
{
	m_object->setSprite(0,0);
}