#pragma once
#include "entity.h"
#include <assert.h>

enum g_state{left,right,am_dead};
#define max_states 3
class goomba: public entity
{
private:
	g_state state;
public:
	// constructor/destructor
	goomba();
	~goomba();

	//member functions
	void update(float timePassed);
	void animate();
};