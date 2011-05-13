#pragma once
#include "entity.h"

enum obstacleStates{sprite1,sprite2,sprite3};

class obstacle: public entity
{
private:
	obstacleStates state;
	float time;

public:

	// constructor/desctructor
	obstacle();
	~obstacle();
	void update(float timePassed);
	void animate();
};