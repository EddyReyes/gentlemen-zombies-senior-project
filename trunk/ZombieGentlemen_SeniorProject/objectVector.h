#pragma once
#include "object.h"

class objectVector
{
private: 
	object ** list;
	int size;
	int memoryIncriment;
public:
	objectVector()
	{
		list = NULL;
		size = NULL;
		memoryIncriment = 1;
	}
	~objectVector()
	{
		for(int i = 0; i < size; i++)
		{
			list[i] = NULL;
		}
	}
	void destroyAllObjects()
	{
		for(int i = 0; i < size; i++)
		{
			if(list[i] != NULL)
				list[i]->~object();
		}
	}
	bool destroyObject(int index)
	{
		if(index < 0 || index > endOfList())
			return false;
		if(list[index])
		{
			list[index]->~object();
			return true;
		}
		else return false;
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
		return size;
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
		if(endOfList() != size)
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
		if(index >= endOfList() || index < 0)
			return false;
		for(int i = index; i < (endOfList() -1); i++)
		{
			swap(i, (i+1));
		}
		return pop();
	}
	bool pop()
	{
		if(destroyObject(endOfList()-1))
		{
			list[(endOfList()-1)] = NULL;
			return true;
		}
		else return false;
	}
	void contractList()
	{
		// set the new size
		size = endOfList();
		// create a new temporary list
		object ** newList = new object * [size];
		// fill in the new list with NULL pointers
		for(int i = 0; i < size; i++)
		{
			newList[i] = NULL;
		}
		// copy over data from current list to new list
		for(int i = 0; i < size; i++)
		{
			newList[i] = list[i];
			// set pointers in old list as NULL
			list[i] = NULL;
		}
		delete [] list;
		list = newList;
	}

	void swap(int index1, int index2)
	{
		object * temp = list[index1];
		list[index1] = list[index2];
		list[index2] = temp;
	}
	int getSize()
	{
		return size;
	}
};