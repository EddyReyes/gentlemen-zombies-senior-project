#include "obstacle.h"

/******************
constructor
sets m_object to NULL
******************/
obstacle::obstacle()
{
	m_object = NULL;
	time = 0;
}

/******************
constructor
does nothing for now, since the object is part of the object manager,
and destruction of all objects is handle there
******************/
obstacle::~obstacle()
{
	
}
void obstacle::update(float timePassed)
{
	time += timePassed;

	if(time <= 0.3)
	{
		switch(state)
		{
		case sprite1:
			m_object->setSprite(0, 0);
			state = sprite2;
			break;
		case sprite2:
			m_object->setSprite(0, 1);
			state = sprite3;
			break;
		case sprite3:
			m_object->setSprite(0, 2);
			state = sprite1;
			break;
		}

		time = 0;
	}


}
