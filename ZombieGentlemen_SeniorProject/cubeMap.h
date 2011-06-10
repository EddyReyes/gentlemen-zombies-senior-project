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

class cubeMap
{
private:
	grid * m_grid;
	float scale;
	int textureRows, textureColumns;
	std::string mapTexture;
	LPDIRECT3DTEXTURE9 * texture;	// map texture
	D3DXIMAGE_INFO * imageInfo;	// contains image parameters
	char ** m_map;
	dxCubePointer ** cubes;
	dxManager * dxMgr;
	int width, height;
	bool toggle, backFaceCulling;

public:
	cubeMap();
	cubeMap(std::string textFile, std::string a_textureFile, dxManager * a_dxMgr);
	~cubeMap();
	void initMap();
	void initCubes();
	void loadMap(std::string filename);
	void draw();
	void toggleMap();
	void initMapTextures();
	void initCubePositions();
	void initCubeScales();
	void checkBackFaceCulling();
	float getScale();
	grid * getGrid();
	int getWidth();
	int getHeight();
};