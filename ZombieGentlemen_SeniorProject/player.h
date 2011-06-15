#pragma once

#include "entity.h"
#include "sound.h"

enum playerState{idle, walkingRight, walkingLeft, jumping, dying, dead};
enum playerSprite{playerSprite1, playerSprite2, playerSprite3, playerSprite4, playerSprite5};

class player: public entity
{
private:
	playerState state;
	playerSprite sprites;
	float timer, armorTimeout, keyTimeout, randomIdle;
	bool armorBlink, armorLoss, keyBlink, hasKey;
	sound * soundMgr;
	int jumpCounter, jumpInterval;

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
	
	// armor
	void removeArmor();
	bool getAmorBlink();
	void armorPickup();
	
	// key
	void keyPickup();
	void removeKey();
	bool getKeyBlink();
	bool playerHasKey();


	void flip();
	void setDirection(char dir);

	void setSound(sound * a_soundMgr);
};