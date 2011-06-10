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
	float scale, depth, xOffset, yOffset, gridScale;
	int textureRows, textureColumns;
	std::string mapTexture;
	LPDIRECT3DTEXTURE9 * texture;	// map texture
	D3DXIMAGE_INFO * imageInfo;	// contains image parameters
	char ** m_map;
	XYPlanePointer ** planes;
	dxManager * dxMgr;
	int width, height;
	bool toggle;

public:
	planeMap();
	planeMap(std::string textFile, std::string a_textureFile, dxManager * a_dxMgr);
	~planeMap();
	void initMap();
	void initPlanes();
	void loadMap(std::string filename);
	void draw();
	void toggleMap();
	void initMapTextures();
	void initPlanePositions();
	void initPlaneScales();
	float getScale();
	grid * getGrid();
	int getWidth();
	int getHeight();
	void offsetMap(D3DXVECTOR3 offset);
};