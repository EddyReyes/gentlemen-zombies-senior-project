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
	int index;

public:
	
	objectManager()
	{
		// set all pointers to NULL
		dxMgr = NULL;
		list = NULL;
		colMap = NULL;
		colMapRects = NULL;
		images = NULL;
		index = 0;
	}

	/******************************************************************
	* Initializer functions
	* These functions are use to initialize ojbectManager data
	*******************************************************************/
	void initObjectMgr(dxManager * a_dxMgr)
	{
		dxMgr = a_dxMgr;
	}

	void initColMap(std::string filename, cubeMap * map)
	{
		colMap = new collisionMap();
		colMap->initCollMap(filename, map);
		colMapRects = colMap->getList();
	};

	void initImages(std::string filename)
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
	void loadObjectsFromTxtFile(std::string filename)
	{
		// load the file into memory
		std::fstream file(filename.c_str());
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
		updatePosiitonRecords();
		clearObjects();
		list->setObjectIndexes();
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

	void draw()
	{
		for(int i = 0; i < list->endOfList(); i++)
		{
			list->get(i)->draw();
		}
	}
	void pop()
	{
		if(!list->pop())
		{
			MessageBox(NULL,"could not pop object list","Object Manager",MB_OK);
		}
		else
		{
			list->contractList();
		}
		if(index > list->endOfList()-1)
			index = list->endOfList()-1;
	}
	object * getObject(){return list->get(index);}
	void indexNext()
	{
		if(index < list->endOfList()-1)
			index++;
	}
	void indexPrev()
	{
		if(index > 0)
			index--;
	}
	void moveObject(D3DXVECTOR3 move)
	{
		if(index >= 0)
		{
			object * obj = list->get(index);
			obj->recordPosition();
			D3DXVECTOR3 * pos = obj->getPosition();
			pos->x += move.x;
			pos->y += move.y;
			pos->z += move.z;
			obj->getCollisionRect()->update();
		}
	}
	void updatePhysics(float deltaTime)
	{
		object * obj;
		for (int i=0; i<list->endOfList(); i++) 
		{
			obj = list->get(i);
			if(obj)
			{
				D3DXVECTOR3 * pos = obj->getPosition();
				if(obj->getPhysics())
				{
					physics * phys = obj->getPhysics();
					phys->update(deltaTime);
					phys->updatePosition(pos);
					phys->onGroundOff();
				}
				obj->getCollisionRect()->update();
			}
		}
	}
	void handleCollision()
	{
		//clearObjects();
		object * obj1;
		object * obj2;

		// check other objects
		for (int i=0; i<list->endOfList(); i++) 
		{
			obj1 = list->get(i);
			if(obj1 != NULL)
			{
				for (int j=i+1; j<list->endOfList(); j++) 
				{
					obj2 = list->get(j);
					if(obj2 != NULL)
					{
						obj1->setTargetCollision(obj2->getCollisionRect());
						obj2->setTargetCollision(obj1->getCollisionRect());
						obj1->checkCollision();
						obj2->checkCollision();
					}
				}
			}
		}
		//check map for collision
		for (int i=0; i<list->endOfList(); i++) 
		{
			obj1 = list->get(i);
			if(obj1 != NULL)
			{
				for(int i = 0; i <= colMap->getSize()-1; i++)
				{
					obj1->setTargetCollision(colMapRects[i]);
					obj1->checkCollision();
				}
			}
		}

		//update physics and handle collision if colliding 
		for (int i=0; i<list->endOfList(); i++) 
		{
			obj1 = list->get(i);
			if(obj1 != NULL)
			{
				// check if object has collided with the bottom boundary
				// if it has then send it back to the top
				if(obj1->getCollisionRect()->collided(colMapRects[colMap->getSize()-1]->getRect())
				   || (obj1->getPosition()->y < colMapRects[colMap->getSize()-1]->getYPosition()))
				{
					obj1->setPosition(obj1->getPosition()->x, obj1->getCollisionRect()->getHeight() * -1 + 0.1f, obj1->getPosition()->z); 
				}
				else if(obj1->isColliding())
				{
					obj1->updatePhysics();
					obj1->handleCollision();
				}
			}
		}

		// update position records and clear 
		updatePosiitonRecords();
		clearObjects();
	}

	void clearObjects()
	{
		object * obj;
		for(int i = 0; i < list->endOfList(); i++)
		{
			obj = list->get(i);
			if(obj != NULL)
				obj->clear();
		}
	}

	void updatePosiitonRecords()
	{
		object * obj;
		for(int i = 0; i < list->endOfList(); i++)
		{
			obj = list->get(i);
			if(obj != NULL)
				obj->recordPosition();
		}
	}

	~objectManager()
	{
		list->destroyAllObjects();
		list->~objectVector();
		colMap->~collisionMap();
	}

	bool setIndex(int a_index)
	{
		if(a_index < list->endOfList()-1 && a_index > 0)
		{
			index = a_index;
			return true;
		}
		else return false;
	}
	bool popObject(int a_index)
	{
		if(a_index < list->endOfList()-1 && a_index > 0)
		{
			// from the ouside of this class, an accurate method of removing
			// any particular object, is to tell the object manager to remove it
			// according to the index it recorded within itself
			bool success; // keeps track of wether the remove was worked
			success = list->remove(a_index); // removes an object by index
			list->setObjectIndexes(); // updates each objects index
			return success;
		}
		else return false;
	}
	int getIndex(){return index;}
	object * getObjectByIndex(int a_index)
	{
		if(a_index < list->endOfList()-1 && a_index > 0)
		{
			return list->get(a_index);
		}
	}

	void indexEnd(){index = list->endOfList()-1;}
	void indexBegining(){index = 0;}
};