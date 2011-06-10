#include "cubeMap.h"

cubeMap::cubeMap(){}
cubeMap::cubeMap(std::string textFile, std::string a_textureFile, dxManager * a_dxMgr)
{
	dxMgr = a_dxMgr;
	texture = new LPDIRECT3DTEXTURE9;
	imageInfo = new D3DXIMAGE_INFO;
	mapTexture = a_textureFile;
	loadMap(textFile);
	m_grid = new grid(height, width, scale);
	initMap();
}
cubeMap::~cubeMap()
{
	// call the grid destructor
	if(m_grid)
	{
		m_grid->~grid();
		m_grid = NULL;
	}
	// delete the cube 2D array
	if(cubes)
	{
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				if(cubes[y][x].cube != NULL)
				{
					cubes[y][x].cube->~dxCube();
					cubes[y][x].cube = NULL;
				}
			}
			delete [] cubes[y];
		}
		delete [] cubes;
		cubes = NULL;
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

	// destroy image and data
	if(texture)
	{
		(*texture)->Release();
		texture = NULL;
	}
}

void cubeMap::initMap()
{
	initCubes();
	initCubePositions();
	initMapTextures();
	initCubeScales();
	checkBackFaceCulling();
}
void cubeMap::initCubes()
{
	// load texture into memory ONCE
	D3DXCreateTextureFromFile(pd3dDevice, mapTexture.c_str(),texture);
	// load image info from file in file name array
	D3DXGetImageInfoFromFile(mapTexture.c_str(), imageInfo);

	cubes = new dxCubePointer * [height];
	for(int y = 0; y < height; y++)
	{
		cubes[y] = new dxCubePointer[width];
		//initialize cubes positions
		for(int x = 0; x < width; x++)
		{
			if(m_map[y][x] != '.')
			{
				cubes[y][x].cube = new dxCube(dxMgr, texture, imageInfo);
			}
			else 
			{
				cubes[y][x].cube = NULL;
			}
		}
	}
}
void cubeMap::loadMap(std::string filename)
{
	std::fstream file(filename.c_str());
	// the size of the data we are going to create
	file >> height >> width >> textureRows >> textureColumns >> scale >> backFaceCulling;
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
void cubeMap::draw()
{
	if(toggle)
	{
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				if(cubes[y][x].cube != NULL)
				{
					cubes[y][x].cube->draw();
				}
			}
		}
	}
}
void cubeMap::toggleMap(){toggle = !toggle;}
void cubeMap::initMapTextures()
{
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			if(cubes[y][x].cube != NULL)
			{
				cubes[y][x].cube->setImageRowsColumns(textureRows, textureColumns);
				cubes[y][x].cube->selectTextureSource(0,0);
				switch(tolower(m_map[y][x]))
				{
				case '.':  cubes[y][x].cube->toggleCubeOff(); break;

				case 'a':  cubes[y][x].cube->selectTextureSource(0,0); break;
				case 'b':  cubes[y][x].cube->selectTextureSource(0,1); break;
				case 'c':  cubes[y][x].cube->selectTextureSource(0,2); break;
				case 'd':  cubes[y][x].cube->selectTextureSource(0,3); break;
				case 'e':  cubes[y][x].cube->selectTextureSource(0,4); break;

				case 'f':  cubes[y][x].cube->selectTextureSource(1,0); break;
				case 'g':  cubes[y][x].cube->selectTextureSource(1,1); break;
				case 'h':  cubes[y][x].cube->selectTextureSource(1,2); break;
				case 'i':  cubes[y][x].cube->selectTextureSource(1,3); break;
				case 'j':  cubes[y][x].cube->selectTextureSource(1,4); break;

				case 'k':  cubes[y][x].cube->selectTextureSource(2,0); break;
				case 'l':  cubes[y][x].cube->selectTextureSource(2,1); break;
				case 'm':  cubes[y][x].cube->selectTextureSource(2,2); break;
				case 'n':  cubes[y][x].cube->selectTextureSource(2,3); break;
				case 'o':  cubes[y][x].cube->selectTextureSource(2,4); break;

				case 'p':  cubes[y][x].cube->selectTextureSource(3,0); break;
				case 'q':  cubes[y][x].cube->selectTextureSource(3,1); break;
				case 'r':  cubes[y][x].cube->selectTextureSource(3,2); break;
				case 's':  cubes[y][x].cube->selectTextureSource(3,3); break;
				case 't':  cubes[y][x].cube->selectTextureSource(3,4); break;

				case 'u':  cubes[y][x].cube->selectTextureSource(4,0); break;
				case 'v':  cubes[y][x].cube->selectTextureSource(4,1); break;
				case 'w':  cubes[y][x].cube->selectTextureSource(4,2); break;
				case 'x':  cubes[y][x].cube->selectTextureSource(4,3); break;
				case 'y':  cubes[y][x].cube->selectTextureSource(4,4); break;

				case 'z':  cubes[y][x].cube->toggleCubeOff(); break;

				default : char buffer[50];
					sprintf_s(buffer, "Invalid map texture character at:  %i, %i", x, y);
					MessageBox(NULL, buffer, "Map Error", MB_OK);
					break;
				}
			}
		}
	}
}
void cubeMap::initCubePositions()
{
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			if(cubes[y][x].cube != NULL)
			{
				D3DXVECTOR3 * pos = m_grid->getNode(y, x);
				cubes[y][x].cube->setPosition(*pos);
			}
		}
	}
}
void cubeMap::initCubeScales()
{
	if(scale <= 0) MessageBox(NULL, "Map scale is invalid", "Map Error", MB_OK);
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			if(cubes[y][x].cube != NULL)
			{
				cubes[y][x].cube->setScale(scale);
			}
		}
	}
}
void cubeMap::checkBackFaceCulling()
{
	if(!backFaceCulling)
	{
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				if(cubes[y][x].cube != NULL)
				{
					cubes[y][x].cube->toggleTransparencyCulling();
				}
			}
		}
	}
}
float cubeMap::getScale(){return scale;}
grid * cubeMap::getGrid(){return m_grid;}
int cubeMap::getWidth(){return width;}
int cubeMap::getHeight(){return height;}