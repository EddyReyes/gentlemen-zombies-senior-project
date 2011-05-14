#include "goomba.h"

goomba::goomba()
{
	type = enemyEntity;
	m_object = NULL;
	state = right;
}

goomba::~goomba()
{
	// destruction of the goomba object will happen in the object manager
}
/**
*uses states to determine which direction its move and also what to do
*should change direction when collision with a wall happens
**/
void goomba::update(float timePassed)
{
	D3DXVECTOR3 temp = *m_object->getPosition();
	switch(state)
	{
	case left:temp.x-=1*timePassed;break;
	case right:temp.x+=1*timePassed;break;
	case am_dead:break;
	default:
		assert(state>=max_states);
	}
	m_object->setPosition(temp);
}
void goomba::animate()
{

}