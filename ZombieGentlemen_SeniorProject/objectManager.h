#pragma once
#include "object.h"
#include "objectVector.h"
#include "collisionMap.h"
#include "imageManager.h"

class objectManager
{
private:
	objectList list; //list that will hold all the objects
	collisionMap * colMap; // map of collision rectangles
	collisionRect ** colMapRects; // list of static (map) collision rects
	imageManager * images; // list of images for objects to use
	dxManager * dxMgr; // dxManager for images to use

public:
	
	objectManager()
	{
		// set all pointers to NULL
		dxMgr = NULL;
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

	void loadObjectsFromTxtFile(char * filename)
	{
		// load the file into memory
		std::fstream file(filename);
		// count the number of objects in the file
		int numObjects = 0;
		file.peek();
		while(!file.eof())
		{
			int c;
			c = file.get();
			if(c == '\n' || file.eof()) 
			{numObjects++;}
		}
		// clear fstream flags
		file.clear();
		// set fstream get pointer back to the beginning
		file.seekg(0, std::ios::beg);

		// create a new object
		// load data into it
		// hand it off to the object vector
	}

	/******************************************************************
	* Loading functions
	* These functions are use to create new objects and load them into 
	* the list
	*******************************************************************/

	void loadCubeObjectToList(dxCube * a_cube, char* textFile)
	{
		object * newObject = new object(a_cube, textFile);
		list.add(newObject);
	}
	void loadPlaneObjectToList(XYPlane * a_plane, char* textFile)
	{
		object * newObject = new object(a_plane, textFile);
		list.add(newObject);
	}
	void loadPlaneObjectToList(dxManager * dxMgr, std::string imgFile, char * textFile)
	{
		object * newObject = new object(dxMgr, imgFile, textFile);
		list.add(newObject);
	}

	~objectManager()
	{
		colMap->~collisionMap();
	}
};