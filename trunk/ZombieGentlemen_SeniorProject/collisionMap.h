#pragma once
#include "grid.h"
#include <stdio.h>
#include <fstream>
#include <ctype.h>
#include <string.h>
#include"cubeMap.h"
#include"planeMap.h"

class collisionMap
{
private:
	char ** map;
	int width, height;
	collisionRect * rects;
	grid * m_grid;
	float scale;
public: 
	collisionMap()
	{
		map = NULL;
		rects = NULL;
		//grid = NULL;
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

		std::fstream file(filename);
		// the size of the data we are going to create
		file >> height >> width;
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

		void envCollMap();
	}
	
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
};