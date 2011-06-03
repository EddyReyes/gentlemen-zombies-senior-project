#pragma once
#include "entity.h"

enum projectileState{projectileIdle, projectileFire, projectileHit};
enum projectileHorizontalFire{noneHor, left, right};
enum projectileVerticalFire{noneVert, up, down};

class projectile : public entity
{
private:
float time;
projectileState state;
projectileHorizontalFire horizontal;
projectileVerticalFire vertical;
float speed;
D3DXVECTOR3 pos;

public:
	projectile();
	~projectile();
	void update(float timePassed);
	void init(D3DXVECTOR3 initPos, float a_speed);
	void animate();
	void reset();
	void setDirection(int wallState, int turretState);
	void firing(float updateTime);
	void setSpeed(float a_speed);
	void hit();
	void fire();
	void flip();
};