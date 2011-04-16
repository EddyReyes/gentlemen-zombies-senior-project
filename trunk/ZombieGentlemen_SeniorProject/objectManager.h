#pragma once
#include <vector> 
using namespace std; //requred to use the STL vector
#include "object.h"

//#define test

class objectManager
{
public:
	


#ifndef test
	objectManager()
	{
		list.clear(); //drops all members from the list and calls there destructors
	}
	void assert(object *a_obj) //takes in object to put into the list
	{
		list.push_back(a_obj);//inserts the object to the back of the list
	}
	object* get(int index)
	{
		return list.at(index); //gets an object at an index
	}
	void remove(int index)//removes object from list
	{
		//uses an iterator i.e. list.begin() and goes to that index and erases it
		//will effectively reduce the size of the list as well
		list.erase(list.begin()+index); 
	}
	int getsize() {return list.size();}//returns the size of the list
	~objectManager()
	{
		list.clear(); 
	}
private:
	vector<object*> list; //list that will hold all the objects
#endif
};