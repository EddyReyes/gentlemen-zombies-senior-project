/*
*Written by: Michael Knoche
*Notes: still a work in progress, needs player class in order to further develop
*/
struct item
{
	int m_price; //defined price of the item
	char m_type; //defines what the item is i.e armor,weapon,healing
	item()//default constructor
	{
		m_price=0;
		m_type=NULL;
	}
	//accessors
	void setPrice(int a_price){m_price=a_price;}
	int getPrice(){return m_price;}
	void setType(char a_type){m_type=a_type;}
	char getType(){return m_type;}
};
class store
{
protected:
	item* merch;//array of items
	int size; //keeps track of array size
public:
	store()
	{
		//TODO: make is so list is initialized with a txt file
		size = 3;
		merch = new item[size];
		for(int c=0;c<size;++c)
		{
			merch[c].setPrice(10);
			merch[c].setType('a');
		}
	}
	item getitem(int index){return merch[index];}//returns item with index
	void printlist()//prints items in the array
	{
		for(int b=0;b<size;++b)
			printf("TYPE: %c PRICE:%d\n",merch[b].getType(),merch[b].getPrice());
	}
	//function to have player buy item(s)
	//will be changed later when player class is finalized
	item buyItem(int index,int &cash)
	{
		item temp = getitem(index);
		cash-=temp.getPrice();
		return temp;
	}
	//function to sell item(s)
	//will also be changed when player class is finalized
	void sellItem(item toSell,int &cash)
	{
		cash+=toSell.getPrice();
	}
	~store()//deconstructor
	{
		delete [] merch;
		merch = NULL;
	}
};