#pragma once
#include "grid.h"
#include <stdio.h>
#include <fstream>
#include <ctype.h>
#include <string.h>
#include"cubeMap.h"
#include"planeMap.h"

#define debug
//#define tomCode

struct collisionRectPointer
{
	collisionRect * colRect;
};

#ifdef tomCode
struct env_collisionRect
{
	int x1;
	int x2;
	int y1;
	int y2;
};
#endif

class collisionMap
{
private:
	char ** map;
	int width, height;
	collisionRectPointer ** rects;
	collisionRect ** rectList;
	int listSize;
	grid * m_grid;
	float scale;
public: 
	collisionMap()
	{
		map = NULL;
		rects = NULL;
		m_grid = NULL;
		scale = NULL;
		listSize = 0;
	}
	collisionMap(std::string filename, cubeMap * a_map)
	{
		listSize = 0;
		initCollMap(filename, a_map);
	}
	~collisionMap()
	{
		// delete map character data
		for(int y = 0; y < height; y++)
		{
			delete [] map[y];
		}
		delete [] map;

		// destroy collision rects and delete the pointers
		for(int i = 0; i < listSize; i++)
		{
			rectList[i]->~collisionRect();
			delete rectList[i];
			rectList[i] = NULL;
		}
		delete [] rectList;
	}

	void initCollMap(std::string filename, cubeMap * sourceMap)
	{
		m_grid = sourceMap->getGrid();
		scale = sourceMap->getScale();
		width = sourceMap->getWidth();
		height = sourceMap->getHeight();

		std::fstream file(filename.c_str());
		/*printf("file size %dx%d\n", m_width, m_height);*/
		map = new char * [height];
		for(int c = 0; c < height; c++){
			map[c] = new char [width];}
		// get the data from the file into the 2D array
		int c;
		for(int y = 0; y < height; ++y){
			for(int x = 0; x < width; ++x){
				//putchar(fileData[y][x]);
				c = file.get();
				if(c == '\n' || c == '\r'){
					x--;}
				else{
					map[y][x] = c;
				}
			}
		}
		// generate a 2D array of pointers to the rects
		generateRects();
		// from the 2D array create a 1D list
		makeOneDimentionalList();
		// destroy 2D list
		destroy2DRectsList();
	}

	void generateRects()
	{
		rects = new collisionRectPointer * [height];
		for(int y = 0; y < height; y++)
		{
			rects[y] = new collisionRectPointer[width];
			for(int x = 0; x < width; x++)
			{
				rects[y][x].colRect = NULL;
			}
		}
		for(int y = 0; y < height; y++)
		{
			//initialize cubes positions
			collisionRectPointer lastRect;
			for(int x = 0; x < width; x++)
			{
				if(map[y][x] == '.')
				{
					rects[y][x].colRect = NULL;
				}
				else
				{
					if(map[y][x] == 'x')
					{
						if(x>0)
						{
							if(map[y][x-1] == '.')
							{
								D3DXVECTOR3 * pos = m_grid->getNode(y, x);
								rects[y][x].colRect = new collisionRect();
								rects[y][x].colRect->modifyParameters(pos->x, pos->y, 1*scale, -1*scale);
								lastRect.colRect = rects[y][x].colRect;
							}
						}
						else if(x==0)
						{
							D3DXVECTOR3 * pos = m_grid->getNode(y, x);
							rects[y][x].colRect = new collisionRect();
							rects[y][x].colRect->modifyParameters(pos->x, pos->y, 1*scale, -1*scale);
							lastRect.colRect = rects[y][x].colRect;
						}
						if(lastRect.colRect != rects[y][x].colRect)
						{
							lastRect.colRect->modifyParameters(lastRect.colRect->getXPosition(), lastRect.colRect->getYPosition(),
								lastRect.colRect->getWidth() + 1*scale, lastRect.colRect->getHeight());
						}
					}
				}
			}
		}
	}
	void makeOneDimentionalList()
	{
		listSize = 0;
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				if(rects[y][x].colRect != NULL)
				{
					listSize++;
				}
			}
		}
		listSize += 4;
		// make a list with enough room for all the collision rects in the map as well as 
		// 3 bounding rects for that surround the world
		rectList = new collisionRect * [listSize];
		int counter = 0;
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				if(rects[y][x].colRect != NULL)
				{
					rectList[counter] = rects[y][x].colRect;
					counter++;
				}
			}
		}	

		// add map boundaries
				
		// left boundary
		rectList[listSize-1] = new collisionRect();
		rectList[listSize-1]->modifyParameters(-1 * scale, 100 * scale, (float)scale,(float)((100 * scale + height) * -1 * scale));

		// right boundary
		rectList[listSize-2] = new collisionRect();
		rectList[listSize-2]->modifyParameters((float)width * scale, 100 * scale, (float)scale, (float)((100 * scale + height) * -1 * scale));
		
		// bottom boundary
		rectList[listSize-3] = new collisionRect();
		rectList[listSize-3]->modifyParameters(-1 * scale,(float)(height * -1 * scale),(float)((width + 1) * scale),(float)(((height * -1) -1) * scale));

		// top boundary
		rectList[listSize-4] = new collisionRect();
		rectList[listSize-4]->modifyParameters(-1 * scale, 100 * scale,(float)((width + 1) * scale), -1 * scale);
	}
	void destroy2DRectsList()
	{
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				if(rects[y][x].colRect != NULL)
				{
					rects[y][x].colRect = NULL;
				}
			}
			delete [] rects[y];
		}
		delete [] rects;
	}
	collisionRect ** getList()
	{
		return rectList;
	}
	int getSize(){return listSize;}
	

#ifdef tomCode

	//Tom's code starts here.
	void envCollMap(int px, int py)
	{

		bool found;
		int maxWidth = 0;

		//This checks to make sure that the function checks by starting at a collidable object 'x'.
		//It also checks to make sure that the collidable object is not already in a rect, and moves on.
		//The first point will always be a collidable object.

		if (map[py][px] == 'x')
		{
			for(int i=0; i < num_env_rects; i++)
			{
				if(py >= env_rect[i]->y1 && py <= env_rect[i]->y2 && px >= env_rect[i]->x1 && px <= env_rect[i]->x2)
				{
					return;
				}
			}
		}
		else
		{
			return;
		}


		//Measures the width of the collidable objects to establish the rect.
		while(!found)
		{
			if(map[py][px + maxWidth] == '.')
			{
				found = true;
			}
			else
			{
				maxWidth++;
			}
		}
		found = false;

		int maxHeight = 0;

		//Measure the height, allowing us to finish checking faster.
		while(!found)
		{
			if(map[py+maxHeight][px] == '.')
			{
				found = true;
			}
			else
			{
				maxHeight++;
			}
		}
		
		int count = 0;
		int maxCount = 0;
		int height = 0;
		int width = 0;

		//These loops build the shape of the rect to be built.
		for(int x = maxWidth - 1; x >= 0; x--)
		{
			for(int y = 0; y < maxHeight && !found; y++)
			{
				for(int x2 = 0; x2 <= x && !found; x2++)
				{
					if(map[py + y][px + x2] == '.')
					{
						found = true;
					}
				}
			
				
				//This helps to build the rect by tracking the biggest rect out of the collidable objects.
				if(!found)
				{
					count = (x + 1) * (y + 1);
						if(count > maxCount)
						{
							maxCount = count;
							width = x + 1;
							height = y + 1;
						}
				}
			}
		}

		/*Builds the point array with the corresponding points:
		* x1 = upper left
		* y1 = upper right
		* x2 = px + width - 1(To start at zero) = lower left.
		* y2 = py + height - 1(To start at zero) = lower right.
		*/
		//temp_env_rect = one rect in the array.
		env_collisionRect * temp_env_rect = new env_collisionRect;
		env_rect[num_env_rects] = temp_env_rect;
		temp_env_rect->x1 = px;
		temp_env_rect->y1= py;
		temp_env_rect->x2 = px + width - 1;
		temp_env_rect->y2 = py + height - 1;

		/*Problem with this method:
		* Maps must have a single blank space all around it to make sure it does not leave the bounds of the map.
		* This is a minor issue, but it keeps from needing to make less checks to establish rects.
		*/
	}
#endif
};