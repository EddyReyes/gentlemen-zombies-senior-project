#pragma once
#include "grid.h"
#include <stdio.h>
#include <fstream>
#include <ctype.h>
#include <string.h>
#include"cubeMap.h"
#include"planeMap.h"

struct collisionRectPointer
{
	collisionRect * colRect;
};

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
};