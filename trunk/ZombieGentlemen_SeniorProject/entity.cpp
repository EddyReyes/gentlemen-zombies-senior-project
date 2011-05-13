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
void entity::setPosition(float x, float y){m_object->setPosition(x, y, 0);}

// mutators
void entity::setObject(object * a_object){m_object = a_object;}
void entity::entityDead(){alive = false;}
void entity::entityAlive(){alive = true;}

//accessors
object * entity::getObject(){return m_object;}
bool entity::isAlive(){return alive;}
bool entity::hasArmor(){return armor;}