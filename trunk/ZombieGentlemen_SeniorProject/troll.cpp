#include "troll.h"

troll::troll(void)
{
	type = entityTroll;
	m_object = NULL;
	timer = 0;
	state = trollIdle;
	srand(((unsigned int)time(0)));
}

troll::~troll(void)
{
	// destructor does not create or destroy data
}

void troll::update(float timePassed)
{
	timer += timePassed;
	if(timer >= maxTime)
	{
		maxTime = (rand() % 2000)/1000.0f;
		randNum = rand() % 4;
		state = (enum trollStates)randNum;
		timer = 0;
	}

	switch(state)
	{
	case trollIdle: 
		m_object->getPhysics()->setXVelocity(0);
		break;
	case trollWalkingLeft: m_object->getPhysics()->setXVelocity(-3);
		break;
	case trollWalkingRight: m_object->getPhysics()->setXVelocity(3);
		break;
	case trollJumping: m_object->getPhysics()->setYVelocity(30);
		break;
	}
	animate();
}
void troll::animate()
{
	switch(state)
	{
	case trollIdle: m_object->setSprite(0,0);
		break;
	case trollWalkingLeft: m_object->setSprite(0,0);
		break;
	case trollWalkingRight: m_object->setSprite(0,1);
		break;
	case trollJumping: //m_object->setSprite(0,0);
		break;
	}
}
void troll::reset()
{
	alive = true;
	armor = false;
}
void troll::flip()
{
	switch(state)
	{
	case trollWalkingLeft: state = trollWalkingRight;
		break;
	case trollWalkingRight: state = trollWalkingLeft;
		break;
	}
}

void troll::setDirection(char dir)
{
	switch(dir)
	{
	case 'l': state = trollWalkingLeft;
		break;
	case 'r': state = trollWalkingRight;
		break;
	default:
		break;
	}
}