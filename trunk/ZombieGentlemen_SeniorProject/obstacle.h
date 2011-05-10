#pragma once
#include "object.h"

class obstacle
{
private:
	object * m_object;
public:

	// constructor/desctructor
	obstacle();
	~obstacle();

	virtual void update(float) = 0;
	
	void loadTrap();// getting a imag and checking for collition
};