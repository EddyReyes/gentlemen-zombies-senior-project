#pragma once
/**
Map will be used to store the map image and the grid of the world

status: skeleton
*/
#include "grid.h"
#include <stdio.h>
#include <fstream>
#include <ctype.h>
#include <string.h>

struct dxCubePointer
{
	dxCube * cube;
};

class Map
{
private:
	grid * m_grid;
	float scale;
	int textureRows, textureColumns;
	string mapTexture;
	char ** m_map;
	dxCubePointer ** cubes;
	XYPlane * background;
	dxManager * dxMgr;
	int width, height;
	bool useCubes;
	bool toggle;

public:
	Map(){}
	Map(char * textFile, std::string a_textureFile, dxManager * a_dxMgr, bool a_useCubes)
	{
		dxMgr = a_dxMgr;
		mapTexture = a_textureFile;
		loadMap(textFile);
		m_grid = new grid(height, width, scale);
		useCubes = a_useCubes;
		initMap();
	}
	~Map()
	{
		// call the grid destructor
		m_grid->~grid();
		// delete either the cube or plane 2D array
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				cubes[y][x].cube->~dxCube();
			}
			delete [] cubes[y];
		}
		delete [] cubes;

		for(int i = 0; i < height; i++)
		{
			delete [] m_map[i];
		}
		delete [] m_map;
	}

	void initMap()
	{
		initCubes();
		initCubePositions();
		initMapTextures();
		initCubeScales();
	}
	void initCubes()
	{
		cubes = new dxCubePointer * [height];
		for(int y = 0; y < height; y++)
		{
			cubes[y] = new dxCubePointer[width];
			//initialize cubes positions
			for(int x = 0; x < width; x++)
			{
				cubes[y][x].cube = new dxCube(dxMgr, mapTexture);
			}
		}
	}
	void loadMap(char * filename)
	{
		fstream file(filename);
		// the size of the data we are going to create
		file >> height >> width >> textureRows >> textureColumns >> scale;
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
			for(int y = 0; y < height; y++)
			{
				for(int x = 0; x < width; x++)
				{
					cubes[y][x].cube->draw();
				}
			}
		}
	}
	void toggleMap(){toggle?false:true;}
	void initMapTextures()
	{
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				cubes[y][x].cube->setImageRowsColumns(textureRows, textureColumns);
				cubes[y][x].cube->selectTextureSource(0,0);
			/*	case(m_map[y][x])
				{

				}*/
			}
		}
	}
	void initCubePositions()
	{
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				D3DXVECTOR3 * pos = m_grid->getNode(y, x);
				cubes[y][x].cube->setPosition(*pos);
			}
		}
	}
	void initCubeScales()
	{
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				cubes[y][x].cube->setScale(scale);
			}
		}
	}
};