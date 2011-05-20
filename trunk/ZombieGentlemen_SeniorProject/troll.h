#pragma once
#include "entity.h"
#include "time.h"

enum trollStates{trollIdle, trollWalkingLeft, trollWalkingRight, trollJumping};
class troll : public entity
{
private:
	trollStates state;
	float timer, maxTime;
	int randNum;

public:
	troll(void);
	~troll(void);
	void update(float timePassed);
	void animate();
	void reset();
};
