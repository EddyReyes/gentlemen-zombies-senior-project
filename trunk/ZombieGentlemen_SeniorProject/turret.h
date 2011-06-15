#pragma once
#include "entity.h"
#include "projectile.h"

enum turretPosition {faceRight, faceDown, faceUp, faceLeft};
enum turretState {fortyFiveRight, ninety, fortyFiveLeft};

class turret: public entity
{
private:
	turretState state;
	turretPosition wallState;
	projectile * bullets;
	int numProjectiles;
	float turretTimer;
	int bulletIterator;

public:

	turret();
	~turret();
	void update(float timePassed);
	void animate();
	void reset();
	void hideProjectiles();
	void setWall(char side);
	void setProjectiles(object ** a_projectiles, int a_numProjectiles);
	int getNumProjectiles();
	projectile * getProjectile(int index);
	void destroyProjectiles();
	void flip();
	void setDirection(char dir);
};