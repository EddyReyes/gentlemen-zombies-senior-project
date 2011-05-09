#pragma once
#include "object.h"


class entity
{
protected:
	object * m_object;
	bool alive, armor;
	// entitys will also require a state

public:
	// constructor destructor
	entity();
	~entity();

	// member functions
	virtual void animate() = 0;

	//virtual functions (for child classes)
	virtual void update(float) = 0;

	// mutators
	void setObject(object * a_object);
	void entityDead();
	void entityAlive();

	//accessors
	object * getObject();
	bool isAlive();
	bool hasArmor();
};