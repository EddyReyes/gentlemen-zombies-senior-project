#pragma once
#include "object.h"
#include "objectVector.h"
#include "collisionMap.h"

class objectManager
{
private:
	objectList list; //list that will hold all the objects
	collisionMap colMap;
	collisionRect ** colMapRects;

public:
	
	objectManager()
	{
		/*list.initList(1);
		colRects = new collisionRect[10];*/
	}

	void initColMap(char * filename, cubeMap * map)
	{
		colMap.initCollMap(filename, map);
		colMapRects = colMap.getList();
	};

	//void insert(object *a_obj) //takes in object to put into the list
	//{
	//	list.add(a_obj);//inserts the object to the back of the list
	//}
	//object* get(int index)
	//{
	//	return list.get(index); //gets an object at an index
	//}
	//void remove(int index)//removes object from list
	//{
	//	list.remove(index);
	//}
	//int getsize() {return list.getSize();}//returns the size of the list
	//void destroyobject(int index)
	//{
	//	list.destroyObject(index);
	//}
	~objectManager()
	{
		/*list.~objectList();
		delete colRects;*/
	}
	/*int endoflist()
	{
		return list.endOfList();
	}*/

};