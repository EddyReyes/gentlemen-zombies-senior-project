#pragma once
#include "entity.h"
#include <assert.h>

enum goombaStates{goombaWalkLeft, goombaWalkRight};

class goomba: public entity
{
private:
	goombaStates state;
	int sprite;
	float timer;
public:
	// constructor/destructor
	goomba();
	~goomba();

	//member functions
	void update(float timePassed);
	void animate();
	void reset();
};