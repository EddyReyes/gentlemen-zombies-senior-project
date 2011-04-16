#pragma once
#include "object.h"

class objectList
{
private: 
	object ** list;
	int size;
	int memoryIncriment;
public:
	objectList()
	{
		list = NULL;
		size = NULL;
		memoryIncriment = 1;
	}
	~objectList()
	{
		for(int i = 0; i > size; i++)
		{
			list[i] = NULL;
		}
	}
	void destroyObjects()
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
	void setMemoryIncriment(int a_incriment)
	{
		if(a_incriment >= 1)
			memoryIncriment = a_incriment;
	}
	bool isFull()
	{
		for(int i = 0; i < size; i++)
		{
			if(list[i] == NULL)
				return false;
		}
		return true;
	}
	int endOfList()
	{
		for(int i = 0; i < size; i++)
		{
			if(list[i] == NULL)
				return i;
		}
	}
	void add(object * a_object)
	{
		// if list is full, make it bigger
		if(isFull())
		{
			// keep track of old size
			int oldSize = size;
			// set the new size
			size += memoryIncriment;
			// create a new temporary list
			object ** newList = new object * [size];
			// fill in the new list with NULL pointers
			for(int i = 0; i < size; i++)
			{
				newList[i] = NULL;
			}
			// copy over data from current list to new list
			for(int i = 0; i < oldSize; i++)
			{
				newList[i] = list[i];
				// set pointers in old list as NULL
				list[i] = NULL;
			}
			delete [] list;
			list = newList;
		}
		// add the new object
		list[endOfList()] = a_object;
	}
	object * get(int index)
	{
		if(index >= size || index < 0)
			return NULL;
		else
			return list[index];
	}
	bool remove(int index)
	{
		if(index >= size || index < 0)
			return false;
		list[index] = NULL;
		for(int i = index; i < endOfList(); i++)
		{
			swap(i, (i+1));
		}
		return true;
	}
	void swap(int index1, int index2)
	{
		object * temp = list[index1];
		list[index2] = list[index1];
		list[index1] = temp;
	}
	int getSize()
	{
		return size;
	}
};