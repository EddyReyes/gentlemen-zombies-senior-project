#include "entity.h"

// constructor destructor
entity::entity()
{
	m_object = NULL;
	alive = true;
	armor = false;
}
entity::~entity()
{
	// entity does not create or destry objects
}

// set the position of the entity
void entity::setPosition(float x, float y)
{
	m_object->setPosition(x, y, 0);
	m_object->recordPosition();
}
void entity::setPosition(D3DXVECTOR3 vec)
{
	m_object->setPosition(vec);
	m_object->recordPosition();
}
void entity::setDefaultPos(D3DXVECTOR3 * pos)
{
	defaultPos.x = pos->x;
	defaultPos.y = pos->y;
	defaultPos.z = 0; // z is always zero, no matter what
}
void entity::setDefaultPos(float x, float y)
{
	defaultPos.x = x;
	defaultPos.y = y;
	defaultPos.z = 0; // z is always zero, no matter what
}
void entity::moveToDefaultPos()
{
	m_object->setPosition(defaultPos);
	m_object->recordPosition();
}

// mutators
void entity::setObject(object * a_object){m_object = a_object;}
void entity::entityDead(){alive = false;}
void entity::entityAlive(){alive = true;}

//accessors
object * entity::getObject(){return m_object;}
bool entity::isAlive(){return alive;}
bool entity::hasArmor(){return armor;}
int entity::getType(){return type;}