#pragma once

#include "entity.h"

enum playerState{idle, walking, jumping, dead};

class player: public entity
{
private:
	playerState state;

public:
	// constructor/destructor
	player();
	~player();

	// member functions
	void animate();
	void update(float timePassed);
	void move(float x, float y);
};
