#include "teleporter.h"

teleporter::teleporter()
{
	m_object = NULL;
	to_port = NULL;
	animate_state=0;
}
teleporter::~teleporter()
{
}
void teleporter::update(float timePassed)
{
	time += timePassed;
	if(time >= 0.04f)
	{
		animate();
		time = 0;
	}
}
void teleporter::animate()
{
	switch(animate_state)
	{
	case 0:
		m_object->setSprite(0, 0);
		animate_state = 1;
	case 1:
		m_object->setSprite(0, 1);
		animate_state = 2;
	case 2:
		m_object->setSprite(0, 2);
		animate_state = 0;
	}
}