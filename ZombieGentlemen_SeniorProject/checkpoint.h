#pragma once
#include "stuff.h"

enum checkpointState{checkpointInactive, checkpointActive};
class checkpoint: public stuff
{
private:
	checkpointState state;
	int ID;

public:
	checkpoint();
	~checkpoint();
	void update(float timePassed);
	void animate();
	void setID(int a_ID);
	int getID();
};