#include  "stringArray.h"

stringArray::stringArray():size(0), strings(NULL){}
stringArray::~stringArray()
{
	if(strings)
	{
		for(int i = 0; i < size; i++)
		{
			strings[i]->~basic_string();
		}
		delete [] strings;
		strings = NULL;
	}
}
void stringArray::loadFromTextFile(char * filename)
{
	std::fstream file(filename);

	// count the number of strings in the text file
	file.peek();
	while(!file.eof())
	{
		int c;
		c = file.get();
		if(c == '\n' || file.eof()) 
		{size++;}
	}
	// clear fstream flags
	file.clear();
	// set fstream get pointer back to the beginning
	file.seekg(0, std::ios::beg);

	// use height to create the respective rows required
	strings = new std::string * [size];
	for(int y = 0; y < size; y++)
	{
		strings[y] = new std::string;
	}
	//file.ignore(1,0);
	// get the data from the file into the 2D array
	for(int y = 0; y < size; ++y){
		char fileName[100];
		file.getline(fileName, 100);
		strings[y]->append(fileName);
		ZeroMemory(fileName, sizeof(fileName));
	}
}
std::string ** stringArray::getStringArray()
{return strings;}
std::string * stringArray::getStringPtrAt(int index)
{
	if (!(index < 0 || index > size))
	{
		return strings[index];
	}
	else return NULL;
}
std::string stringArray::getStringAt(int index)
{
	if (!(index < 0 || index > size))
	{
		return (*strings[index]);
	}
	else return NULL;
}
int stringArray::getSize(){return size;}