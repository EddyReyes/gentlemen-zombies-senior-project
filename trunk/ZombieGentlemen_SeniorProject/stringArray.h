#pragma once
#include "dxManager.h"
#include <stdio.h>
#include <fstream>
#include <ctype.h>
#include <string.h>

class stringArray
{
private:
	int size;
	std::string ** strings;
public:
	stringArray();
	~stringArray();
	void loadFromTextFile(std::string filename);
	std::string ** getStringArray();
	std::string * getStringPtrAt(int index);
	std::string getStringAt(int index);
	int getSize();
};