#pragma once
#include "object.h"

class obstacle
{
private:
	object * m_ojbect;
public:

	// constructor/desctructor
	obstacle();
	~obstacle();

	// mutators
	void setOjbect();
};