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

	void loadTrap();
};