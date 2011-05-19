#include "checkpoint.h"

checkpoint::checkpoint()
{
	m_object = NULL;
	type = stuff_checkpoint;
	pickedUp = false;
	state = checkpointInactive;
	ID = -1;
}
checkpoint::~checkpoint()
{}
void checkpoint::update(float timePassed)
{
	if(pickedUp)
	{
		state = checkpointActive;
		animate();
	}
}
void checkpoint::animate()
{
	switch(state)
	{
	case checkpointInactive:
		m_object->setSprite(0,0);
		break;
	case checkpointActive:
		m_object->setSprite(0,1);
		break;
	}
}
void checkpoint::setID(int a_ID){ID = a_ID;}
int checkpoint::getID(){return ID;}