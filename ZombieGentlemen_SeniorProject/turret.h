#pragma once
#include "entity.h"

enum turretState {fortyFiveRight, nindy, fortyFiveLeft};

class turret: public entity
{
private:
	turretState state;
	float time;

public:

	turret();

	~turret();
	void update(float timePassed);
};