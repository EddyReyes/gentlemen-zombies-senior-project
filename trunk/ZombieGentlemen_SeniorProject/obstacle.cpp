#include "obstacle.h"

/******************
constructor
sets m_object to NULL
******************/
obstacle::obstacle()
{
	m_object = NULL;
}

/******************
constructor
does nothing for now, since the object is part of the object manager,
and destruction of all objects is handle there
******************/
obstacle::~obstacle()
{
	m_object->~object();
}

/******************
setOjbect
takes in an ojbect pointer and sets it to m_object
******************/
void obstacle::setOjbect(int a_object)
{
	//m_object = a_object;
}