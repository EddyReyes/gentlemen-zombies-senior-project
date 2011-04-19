#pragma once
#include "object.h"
#include "objectVector.h"
#include "collisionMap.h"
#include "imageManager.h"

class objectManager
{
private:
	objectVector * list; //list that will hold all the objects
	collisionMap * colMap; // map of collision rectangles
	collisionRect ** colMapRects; // list of static (map) collision rects
	imageManager * images; // list of images for objects to use
	dxManager * dxMgr; // dxManager for images to use

public:
	
	objectManager()
	{
		// set all pointers to NULL
		dxMgr = NULL;
		list = NULL;
		colMap = NULL;
		colMapRects = NULL;
		images = NULL;
	}

	/******************************************************************
	* Initializer functions
	* These functions are use to initialize ojbectManager data
	*******************************************************************/
	void initObjectMgr(dxManager * a_dxMgr)
	{
		dxMgr = a_dxMgr;
	}

	void initColMap(char * filename, cubeMap * map)
	{
		colMap = new collisionMap();
		colMap->initCollMap(filename, map);
		colMapRects = colMap->getList();
	};

	void initImages(char * filename)
	{
		images = new imageManager();
		images->initImageManager(filename, dxMgr);
	}

	/******************************************************************
	* loadObjectsFromTxtFile
	* This massive function takes in one text file, counts the number of 
	* lines in it, and creates an object vector of that size
	* it then takes all the data in the txt file, creates a new object
	* of the right type, loads in the image data, and all parameters including
	* x, y, z, width, height, rows, columns, left offset, top offset, 
	* right offset, and bottom offset
	* once It has created the object and loaded its parameters, it passes
	* it to the list where it will get dealth with accordingly
	*******************************************************************/
	void loadObjectsFromTxtFile(char * filename)
	{
		// load the file into memory
		std::fstream file(filename);
		// count the number of objects in the file
		int size = 0;
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

		// create a new object vector
		list = new objectVector();
		list->initList(size);
		// loop until object vector is full
		bool loadFail = false;
		for(int i = 0; i < size && !loadFail; i++)
		{
			/****************************** 
			* get the object data
			* c/p (cube, plane), index to image (from image manager),
			* x, y, z, width, height, rows, columns, right offset,
			* left offset, top offset, bottom offset
			*******************************/
			char primitiveType = 0;
			float x = 0, y = 0, z = 0, width = 0, height = 0, depth = 0,
				  leftOffset = 0, topOffset = 0, rightOffset = 0, 
				  bottomOffset = 0;
			int imageRows = 0, imageColumns = 0, imageIndex = 0;
			
			// get data from file
			file >> imageIndex >> primitiveType >> x >> y >> z >> width >> height 
				 >> depth >> imageRows >> imageColumns >> leftOffset >> topOffset >> rightOffset 
				 >> bottomOffset;

			loadFail = verifyData(i, imageIndex, primitiveType, width, height, depth,
					imageRows, imageColumns, leftOffset, topOffset, rightOffset,
					bottomOffset);
			if(loadFail)
			{
				MessageBox(NULL, "failed to load objects", "Object Loading Error", MB_OK);
				break;
			}
			if(primitiveType == 'c')
			{
				dxCube * tempCube = new dxCube(dxMgr, images->getImage(imageIndex), 
					images->getImageInfo(imageIndex));
				// create a new object
				object * temp = new object(tempCube);
				// load data into it
				temp->loadParameters(x, y, z, width, height, depth, imageRows, imageColumns, leftOffset,
					topOffset, rightOffset, bottomOffset);
				// hand it off to the object vector
				list->add(temp);
			}
			else if(primitiveType == 'p')
			{
				XYPlane * tempPlane = new XYPlane(dxMgr, images->getImage(imageIndex), 
					images->getImageInfo(imageIndex));
				// create a new object
				object * temp = new object(tempPlane);
				// load data into it
				temp->loadParameters(x, y, z, width,height, depth, imageRows, imageColumns, leftOffset,
					topOffset, rightOffset, bottomOffset);
				// hand it off to the object vector
				list->add(temp);
			}
		}
	}

	bool verifyData(int objectIndex, int imageIndex, char primitiveType, 
			float width, float height, float depth, int imageRows, int imageColumns, 
			float leftOffset, float topOffset, float rightOffset, float bottomOffset)
	{
		char buffer[50];
		// check that imageIndex is not less than zero and not greater than the size
		// of the imageManager array
		if(imageIndex < 0 || imageIndex > images->getSize() -1)
		{
			// display error message
			sprintf_s(buffer, "Invalid image index at object :  %i", objectIndex);
			MessageBox(NULL, buffer, "Object Loading Error", MB_OK);
			// return that true, signifying failure occured
			return true;
		}
		// check that the primitive type is only 'c' or 'p'
		if(!(primitiveType == 'c' || primitiveType == 'p'))
		{
			// display error message
			sprintf_s(buffer, "Invalid primitive type at object :  %i", objectIndex);
			MessageBox(NULL, buffer, "Object Loading Error", MB_OK);
			// return that true, signifying failure occured
			return true;
		}
		// check if width is less than zero
		if(width <= 0)
		{
			sprintf_s(buffer,"Invalid width at object :%i", objectIndex);
			MessageBox(NULL,buffer,"Object Loading Error",MB_OK);
			return true;
		}
		// check if height is less than zero
		if(height <= 0)
		{
			sprintf_s(buffer,"Invalid height at object :%i", objectIndex);
			MessageBox(NULL,buffer,"Object Loading Error",MB_OK);
			return true;
		}
		// check if depth is less than zero
		if(height <= 0)
		{
			sprintf_s(buffer,"Invalid depth at object :%i", objectIndex);
			MessageBox(NULL,buffer,"Object Loading Error",MB_OK);
			return true;
		}
		// check if imageRows is less than zero
		if(imageRows <= 0)
		{
			sprintf_s(buffer,"Invalid imageRows at object :%i", objectIndex);
			MessageBox(NULL,buffer,"Object Loading Error",MB_OK);
			return true;
		}
		// check if imageCoumns is less than zero
		if(imageColumns <= 0)
		{
			sprintf_s(buffer,"Invalid imageColumns at object :%i", objectIndex);
			MessageBox(NULL,buffer,"Object Loading Error",MB_OK);
			return true;
		}
		// check if leftOffset is less than zero
		if(leftOffset < 0)
		{
			sprintf_s(buffer,"Invalid leftOffest at object :%i", objectIndex);
			MessageBox(NULL,buffer,"Object Loading Error",MB_OK);
			return true;
		}
		// check if topOffset is less than zero
		if(topOffset < 0)
		{
			sprintf_s(buffer,"Invalid topOffset at object :%i", objectIndex);
			MessageBox(NULL,buffer,"Object Loading Error",MB_OK);
			return true;
		}
		// check if rightOffset is less than zero
		if(rightOffset < 0)
		{
			sprintf_s(buffer,"Invalid width at rightOffset :%i", objectIndex);
			MessageBox(NULL,buffer,"Object Loading Error",MB_OK);
			return true;
		}
		// check if bottomOffset is less than zero
		if(bottomOffset < 0)
		{
			sprintf_s(buffer,"Invalid width at bottomeOffset :%i", objectIndex);
			MessageBox(NULL,buffer,"Object Loading Error",MB_OK);
			return true;
		}
		// return that false, signifying all parameters are valid
		return false;
	}
	/******************************************************************
	* Loading functions
	* These functions are use to create new objects and load them into 
	* the list
	*******************************************************************/

	void loadCubeObjectToList(dxCube * a_cube, char* textFile)
	{
		object * newObject = new object(a_cube, textFile);
		list->add(newObject);
	}
	void loadPlaneObjectToList(XYPlane * a_plane, char* textFile)
	{
		object * newObject = new object(a_plane, textFile);
		list->add(newObject);
	}
	void loadPlaneObjectToList(dxManager * dxMgr, std::string imgFile, char * textFile)
	{
		object * newObject = new object(dxMgr, imgFile, textFile);
		list->add(newObject);
	}

	void draw()
	{
		for(int i = 0; i < list->endOfList(); i++)
		{
			list->get(i)->draw();
		}
	}
	~objectManager()
	{
		list->destroyAllObjects();
		list->~objectVector();
		colMap->~collisionMap();
	}
};