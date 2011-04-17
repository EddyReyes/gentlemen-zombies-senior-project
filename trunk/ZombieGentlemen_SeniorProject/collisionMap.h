#pragma once
#include "grid.h"
#include <stdio.h>
#include <fstream>
#include <ctype.h>
#include <string.h>
#include"cubeMap.h"
#include"planeMap.h"

#define debug

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
	}
	collisionMap(char * filename, cubeMap * a_map)
	{
		initCollMap(filename,a_map);
	}
	~collisionMap(){}

	void initCollMap(char * filename, cubeMap * sourceMap)
	{
		m_grid = sourceMap->getGrid();
		scale = sourceMap->getScale();
		width = sourceMap->getWidth();
		height = sourceMap->getHeight();

		std::fstream file(filename);
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
		}
		delete [] rects;
	}
	collisionRect ** getList()
	{
		return rectList;
	}
	
#ifndef debug
	void envCollMap()
	{

		static int py = 0;
		static int px = 0;
		bool found;
		int maxWidth = 0;

		if (map[py][px] == '.')
		{
			for(int i = 0; i < num_rects; i++)
			{
				if(py >= rect[i].y1 && py <= rect[i].y2 && px >= rect[i].x1 && px <= rect[i].x2)
				{

				}
			}
		}

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
			
		

				if(!found)
				{
					count = (x + 1) * (y + 1);
						if(count > maxCount)
						{
							width = x + 1;
							height = y + 1;
						}
				}
			}
		}
	}
#endif
};