/*
*Written by: Michael Knoche
*Notes: redesign is needed
*/
#include "Menu.h"
class store
{
private:
	Menu* main;
	Menu* sub;
	//item* merch;//array of items
	//int size; //keeps track of array size
public:
	store();
	store(char*,char*);

	//item getitem(int index){return merch[index];}//returns item with index
	//void printlist()//prints items in the array
	//{
	//	for(int b=0;b<size;++b)
	//		printf("TYPE: %c PRICE:%d\n",merch[b].getType(),merch[b].getPrice());
	//}
	////function to have player buy item(s)
	////will be changed later when player class is finalized
	//item buyItem(int index,int &cash)
	//{
//		item temp = getitem(index);
//		cash-=temp.getPrice();
//		return temp;
//	}
//	//function to sell item(s)
//	//will also be changed when player class is finalized
//	void sellItem(item toSell,int &cash)
//	{
//		cash+=toSell.getPrice();
//	}
//	~store()//deconstructor
//	{
//		delete [] merch;
//		merch = NULL;
//	}
};