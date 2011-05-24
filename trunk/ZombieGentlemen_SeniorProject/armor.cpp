#include "armor.h"

armor::armor()
{
	time = 0;
	m_object = NULL;
}

armor::~armor(void)
{

}

void armor::update(float timePassed)
{
	time += timePassed;

	animate();

	
	
}

void armor::animate()
{
	m_object->setSprite(0,0);
}