#pragma once
#include "entity.h"
#include "projectile.h"

enum turretPosition {faceRight, faceDown, faceUP, faceLeft};
enum turretState {fortyFiveRight, ninety, fortyFiveLeft};

class turret: public entity
{
private:
	turretState state;
	turretPosition wallState;
	projectile * bullets;
	float time;

public:

	turret();
	~turret();
	void update(float timePassed);
	void animate();
	void reset();
	void setWall(char side);
	void setProjectiles(object * proj1, object * proj2, object * proj3, object * proj4, object * proj5);
};