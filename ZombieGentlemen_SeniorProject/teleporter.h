#pragma once
#include "entity.h"
#include "stuff.h"

class teleporter:public stuff
{
public:
	teleporter();
	~teleporter();
	void update(float timePassed);
	void animate();
	void setData(float,float);
	D3DXVECTOR3 getData();
private:
	float time;
	int animate_state;
	D3DXVECTOR3 tele_vec;//variables where to teleport the player
};