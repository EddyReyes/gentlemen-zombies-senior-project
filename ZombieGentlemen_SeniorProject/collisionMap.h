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
	int width,height;
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
	}
};