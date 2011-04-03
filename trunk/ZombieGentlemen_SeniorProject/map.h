#pragma once
/**
Map will be used to store the map image and the grid of the world

status: skeleton
*/
#include "grid.h"
#include <stdio.h>
#include <fstream>
#include <ctype.h>

class Map
{
private:
	grid * m_grid;
	float scale;
	char ** m_map;
	dxCube ** cubes;
	XYPlane ** planes;
	XYPlane * background;
	dxManager * dxMgr;
	int width, height;
	bool useCubes;
	bool toggle;

public:
	Map(){}
	Map(char * filename, dxManager * a_dxMgr, bool a_useCubes)
	{
		dxMgr = a_dxMgr;
		loadMap(filename);
		m_grid = new grid(height, width, scale);
		useCubes = a_useCubes;
		initMap();
	}
	~Map(){}

	void initMap()
	{
		if(useCubes) initCubes();
		else initPlanes();
	}
	void initCubes()
	{
		cubes = new dxCube * [width];
		for(int y = 0; y < width; y++)
		{
			cubes[y] = new dxCube[height];
			//initialize cubes positions
			for(int x = 0; x < height; x++)
			{
				cubes[y][x] = dxCube(dxMgr, "images/glassPanes2.bmp");
				D3DXVECTOR3 * pos = m_grid->getNode(y, x); 
				cubes[y][x].setPosition(*pos);
				cubes[y][x].setScale(scale);
			}
		}
	}
	void initPlanes()
	{
		planes = new XYPlane * [width];
		for(int y = 0; y < width; y++)
		{
			planes[y] = new XYPlane[height];
			//initialize cubes positions and scale
			for(int x = 0; x < height; x++)
			{
				planes[y][x] = XYPlane(dxMgr, "images/glassPanes2.bmp");
				D3DXVECTOR3 * pos = m_grid->getNode(y, x); 
				planes[y][x].setPosition(*pos);
				planes[y][x].setScale(scale);
			}
		}
	}
	void loadMap(char * filename)
	{
		fstream file(filename);
		// the size of the data we are going to create
		file >> height >> width >> scale;
		/*printf("file size %dx%d\n", m_width, m_height);*/
		m_map = new char * [height];
		for(int c = 0; c < height; c++){
			m_map[c] = new char [width];}
		// get the data from the file into the 2D array
		int c;
		for(int y = 0; y < height; ++y){
			for(int x = 0; x < width; ++x){
				//putchar(fileData[y][x]);
				c = file.get();
				if(c == '\n' || c == '\r'){
					x--;}
				else{
					m_map[y][x] = c;
				}
			}
		}
	}
	void draw()
	{
		if(toggle)
		{
			if(useCubes)
			{
				for(int y = 0; y < width; y++)
				{
					for(int x = 0; x < height; x++)
					{
						cubes[y][x].draw();
					}
				}
			}
			else
			{
				for(int y = 0; y < width; y++)
				{
					for(int x = 0; x < height; x++)
					{
						planes[y][x].draw();
					}
				}
			}
		}
	}

};