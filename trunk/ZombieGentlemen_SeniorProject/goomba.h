#pragma once
#include "entity.h"
#include <assert.h>

enum goombaStates{goombaWalkLeft,goombaWalkRight,goombaDying,goombaDead};
class goomba: public entity
{
private:
	goombaStates state;
public:
	// constructor/destructor
	goomba();
	~goomba();

	//member functions
	void update(float timePassed);
	void animate();
};