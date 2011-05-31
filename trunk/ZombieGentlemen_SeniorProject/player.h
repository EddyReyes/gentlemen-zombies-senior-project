#pragma once

#include "entity.h"

enum playerState{idle, walkingRight, walkingLeft, jumping, dying, dead};

class player: public entity
{
private:
	playerState state;
	float timer, armorTimeout;
	bool armorBlink;

public:
	// constructor/destructor
	player();
	~player();

	// member functions
	void animate();
	void reset();
	void update(float timePassed);
	void move(float x, float y);
	void bounce();
	void removeArmor();
	bool getAmorBlink();
	void armorPickup();
};