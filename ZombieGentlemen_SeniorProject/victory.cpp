#include "victory.h"

victory::victory(void)
{
	m_object = NULL;
	type = stuff_victory;
	pickedUp = false;
}

victory::~victory(void)
{
}
void victory::update(float timePassed)
{
	if(pickedUp)
	{
		animate();
	}
}
void victory::animate()
{
	if(pickedUp)
		m_object->setSprite(0,1);
	else
		m_object->setSprite(0,0);
}