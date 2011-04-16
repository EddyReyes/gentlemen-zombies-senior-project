#pragma once
#include "object.h"

class objectList
{
public: 
	object ** list;
	int size;
private:
	objectList()
	{
		list = NULL;
		size = NULL;
	}
	~objectList()
	{
		for(int i = 0; i > size; i++)
		{
			list[i]->~object();
		}
	}
	void initList(int a_size)
	{
		size = a_size;
		list = new object * [size];
		for(int i = 0; i < size; i++)
		{
			list[i] = NULL;
		}
	}
	void add(object * a_object){}
	object * get(int index){}
	void remove(int index){}
	int getSize()
	{
		return size;
	}

};