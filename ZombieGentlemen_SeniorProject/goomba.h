#pragma once
#include "entity.h"

class goomba: public entity
{
public:
	// constructor/destructor
	goomba();
	~goomba();

	//member functions
	void update(float timePassed);
	void animate();
};