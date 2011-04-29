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

struct XYPlanePointer
{
	XYPlane * plane;
};

class planeMap
{
private:
	grid * m_grid;
	float scale;
	int textureRows, textureColumns;
	std::string mapTexture;
	char ** m_map;
	XYPlanePointer ** planes;
	dxManager * dxMgr;
	int width, height;
	bool toggle;

public:
	planeMap(){}
	planeMap(char * textFile, std::string a_textureFile, dxManager * a_dxMgr)
	{
		dxMgr = a_dxMgr;
		mapTexture = a_textureFile;
		loadMap(textFile);
		m_grid = new grid(height, width, scale);
		initMap();
	}
	~planeMap()
	{
		// call the grid destructor
		if(m_grid)
		{
			m_grid->~grid();
			m_grid = NULL;
		}
		// delete the plane array
		if(planes)
		{
			for(int y = 0; y < height; y++)
			{
				for(int x = 0; x < width; x++)
				{
					if(planes[y][x].plane != NULL)
					{
						planes[y][x].plane->~XYPlane();
						planes[y][x].plane = NULL;
					}
				}
				delete [] planes[y];
			}
			delete [] planes;
			planes = NULL;
		}

		if(m_map)
		{
			for(int i = 0; i < height; i++)
			{
				delete [] m_map[i];
			}
			delete [] m_map;
			m_map = NULL;
		}
	}

	void initMap()
	{
		initPlanes();
		initPlanePositions();
		initMapTextures();
		initPlaneScales();
	}
	void initPlanes()
	{
		planes = new XYPlanePointer * [height];
		for(int y = 0; y < height; y++)
		{
			planes[y] = new XYPlanePointer[width];
			//initialize planes positions
			for(int x = 0; x < width; x++)
			{
				if(m_map[y][x] != '.')
				{
					planes[y][x].plane = new XYPlane(dxMgr, mapTexture);
				}
				else 
				{
					planes[y][x].plane = NULL;
				}
			}
		}
	}
	void loadMap(char * filename)
	{
		std::fstream file(filename);
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
					if(planes[y][x].plane != NULL)
					{
						planes[y][x].plane->draw();
					}
				}
			}
		}
	}
	void toggleMap(){toggle = !toggle;}
	void initMapTextures()
	{
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				if(planes[y][x].plane !=  NULL)
				{
					planes[y][x].plane->setImageRowsColumns(textureRows, textureColumns);
					planes[y][x].plane->selectTextureSource(0,0);
					switch(tolower(m_map[y][x]))
					{
					case '.':  planes[y][x].plane->toggleImageOff(); break;

					case 'a':  planes[y][x].plane->selectTextureSource(0,0); break;
					case 'b':  planes[y][x].plane->selectTextureSource(0,1); break;
					case 'c':  planes[y][x].plane->selectTextureSource(0,2); break;
					case 'd':  planes[y][x].plane->selectTextureSource(0,3); break;
					case 'e':  planes[y][x].plane->selectTextureSource(0,4); break;

					case 'f':  planes[y][x].plane->selectTextureSource(1,0); break;
					case 'g':  planes[y][x].plane->selectTextureSource(1,1); break;
					case 'h':  planes[y][x].plane->selectTextureSource(1,2); break;
					case 'i':  planes[y][x].plane->selectTextureSource(1,3); break;
					case 'j':  planes[y][x].plane->selectTextureSource(1,4); break;

					case 'k':  planes[y][x].plane->selectTextureSource(2,0); break;
					case 'l':  planes[y][x].plane->selectTextureSource(2,1); break;
					case 'm':  planes[y][x].plane->selectTextureSource(2,2); break;
					case 'n':  planes[y][x].plane->selectTextureSource(2,3); break;
					case 'o':  planes[y][x].plane->selectTextureSource(2,4); break;

					case 'p':  planes[y][x].plane->selectTextureSource(3,0); break;
					case 'q':  planes[y][x].plane->selectTextureSource(3,1); break;
					case 'r':  planes[y][x].plane->selectTextureSource(3,2); break;
					case 's':  planes[y][x].plane->selectTextureSource(3,3); break;
					case 't':  planes[y][x].plane->selectTextureSource(3,4); break;

					case 'u':  planes[y][x].plane->selectTextureSource(4,0); break;
					case 'v':  planes[y][x].plane->selectTextureSource(4,1); break;
					case 'w':  planes[y][x].plane->selectTextureSource(4,2); break;
					case 'x':  planes[y][x].plane->selectTextureSource(4,3); break;
					case 'y':  planes[y][x].plane->selectTextureSource(4,4); break;

					case 'z':  planes[y][x].plane->toggleImageOff(); break;

					default : char buffer[50];
						sprintf_s(buffer, "Invalid map texture character at:  %i, %i", x, y);
						MessageBox(NULL, buffer, "Map Error", MB_OK);
						break;
					}
				}
			}
		}
	}
	void initPlanePositions()
	{
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				if(planes[y][x].plane != NULL)
				{
					D3DXVECTOR3 * pos = m_grid->getNode(y, x);
					planes[y][x].plane->setPosition(*pos);
				}
			}
		}
	}
	void initPlaneScales()
	{
		if(scale <= 0) MessageBox(NULL, "Map scale is invalid", "Map Error", MB_OK);
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				if(planes[y][x].plane != NULL)
				{
					planes[y][x].plane->setScale(scale);
				}
			}
		}
	}
	float getScale(){return scale;}
	grid * getGrid(){return m_grid;}
	int getWidth(){return width;}
	int getHeight(){return height;}
};