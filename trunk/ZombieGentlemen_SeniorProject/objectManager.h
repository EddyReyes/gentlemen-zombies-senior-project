#pragma once
#include "object.h"
#include "objectVector.h"
//#define test

class objectManager
{
public:
	


#ifndef test
	objectManager()
	{
		list.initList(10);
		colRects = new collisionRect[10];
	}
	void insert(object *a_obj) //takes in object to put into the list
	{
		list.add(a_obj);//inserts the object to the back of the list
	}
	object* get(int index)
	{
		return list.get(index); //gets an object at an index
	}
	void remove(int index)//removes object from list
	{
		list.remove(index);
	}
	int getsize() {return list.getSize();}//returns the size of the list
	~objectManager()
	{
		list.~objectList();
		delete colRects;
	}
private:
	objectList list; //list that will hold all the objects
	collisionRect* colRects;
#endif
};