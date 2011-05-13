#pragma once
#include "entity.h"
#include "projectile.h"

enum turretState {fortyFiveRight, ninety, fortyFiveLeft};

class turret: public entity
{
private:
	turretState state;
	float time;

public:

	turret();
	~turret();
	void update(float timePassed);
	void animate();
};