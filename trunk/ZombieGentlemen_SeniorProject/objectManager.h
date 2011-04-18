#pragma once
#include "object.h"
#include "objectVector.h"
#include "collisionMap.h"
#include "imageManager.h"

class objectManager
{
private:
	objectList list; //list that will hold all the objects
	collisionMap * colMap;
	collisionRect ** colMapRects;
	imageManager * images;
	dxManager * dxMgr;

public:
	
	objectManager()
	{
		dxMgr = NULL;
		colMap = NULL;
		colMapRects = NULL;
	}
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
		images->initImageManager(filename, dxMgr);
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