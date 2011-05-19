#pragma once
#include "entity.h"
#include "projectile.h"

enum position {faceRight, faceDown, faceUP, faceLeft};
enum turretState {fortyFiveRight, ninety, fortyFiveLeft};

class turret: public entity
{
private:
	turretState state;
	position	wallState;
	float time;

public:

	turret();
	~turret();
	void update(float timePassed);
	void animate();
	void reset();
	void setWall(char side);
};