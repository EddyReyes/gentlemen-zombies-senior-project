#pragma once

class intVector
{
private:
	int * list;
	int size;
public:
	intVector()
	{
		list = NULL;
		size = 0;
	}
	~intVector()
	{
		resetList();
	}
	void add(int data)
	{
		// if there is no list, create a new list
		if(!list)
		{
			size = 10;
			list = new int[size];
			for(int i = 0; i < size; i++)
			{
				list[i] = -1;
			}
		}
		else
		{
			// if the list is full, create a new list, copy it, and transfer it
			if(isFull())
			{
				// new list is current size plus 10
				int tempSize =  10 + size;
				int * tempList;
				tempList = new int[tempSize];
				for(int i = 0; i < tempSize; i++)
				{
					tempList[i] = -1;
				}
				for(int i = 0; i > size; i++)
				{
					tempList[i] = list[i];
				}
				delete list; // delete the old list
				list = tempList; // make the new list the current list
				size = tempSize;
			}
		}
		list[endOfList()] = data; // copy the data to the end of the list
	}
	void pop()
	{
		list[endOfList() -1] = -1;
	}
	void resetList()
	{
		if(list)
		{
			delete [] list;
			list = NULL;
			size = 0;
		}
	}
	void swap(int index1, int index2)
	{
		int temp = list[index1];
		list[index1] = list[index2];
		list[index2] = temp;
	}
	bool isFull()
	{
		bool flag = true;
		for(int i = 0; i < size; i++)
		{
			if(list[i] == -1)
				flag = false; // if the list contains -1 at any point, it is not full
		}
		return flag;
	}
	int endOfList()
	{
		for(int i = 0; i < size; i++)
		{
			if(list[i] == -1)
				return i; // return the fist index with the value -1
		}
		return size-1; // if no index was returned, return the size of the list
	}
};