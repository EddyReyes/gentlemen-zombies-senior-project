#pragma once
#include "object.h"
#include "imageManager.h"


enum entityType{playerEntity, enemyEntity};
class entity
{
protected:
	object * m_object;
	entityType type;
	bool alive, armor;
	// entitys will also require a state

public:
	// constructor destructor
	entity();
	~entity();

	//virtual functions (for child classes)
	virtual void update(float) = 0;
	virtual void animate() = 0;
	
	// member functions
	void setPosition(float, float);

	// mutators
	void setObject(object * a_object);
	void entityDead();
	void entityAlive();

	//accessors
	object * getObject();
	bool isAlive();
	bool hasArmor();
};