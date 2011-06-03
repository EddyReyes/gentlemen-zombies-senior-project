#pragma once
#include "entity.h"

enum ziggyStates {fly1, fly2, fly3};
enum ziggyDirection{ziggyLeft, ziggyRight};

class ziggy: public entity
{
private:
	ziggyStates state;
	ziggyDirection direction;
	float time;
public:
	ziggy();
	~ziggy();
	void update(float timePassed);
	void animate();
	void reset();
	void flip();
};