#include "planeMap.h"

planeMap::planeMap(){}
planeMap::planeMap(std::string textFile, std::string a_textureFile, dxManager * a_dxMgr)
{
	dxMgr = a_dxMgr;
	texture = new LPDIRECT3DTEXTURE9;
	imageInfo = new D3DXIMAGE_INFO;
	mapTexture = a_textureFile;
	loadMap(textFile);
	m_grid = new grid(height, width, gridScale);
	initMap();
}
planeMap::~planeMap()
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
	// destroy image and data
	if(texture)
	{
		(*texture)->Release();
		texture = NULL;
	}
}

void planeMap::initMap()
{
	initPlanes();
	initPlanePositions();
	initMapTextures();
	initPlaneScales();
}
void planeMap::initPlanes()
{
	// load texture into memory ONCE
	D3DXCreateTextureFromFile(pd3dDevice, mapTexture.c_str(),texture);
	// load image info from file in file name array
	D3DXGetImageInfoFromFile(mapTexture.c_str(), imageInfo);


	planes = new XYPlanePointer * [height];
	for(int y = 0; y < height; y++)
	{
		planes[y] = new XYPlanePointer[width];
		//initialize planes positions
		for(int x = 0; x < width; x++)
		{
			if(m_map[y][x] != '.')
			{
				planes[y][x].plane = new XYPlane(dxMgr, texture, imageInfo);
			}
			else 
			{
				planes[y][x].plane = NULL;
			}
		}
	}
}
void planeMap::loadMap(std::string filename)
{
	std::fstream file(filename.c_str());
	// the size of the data we are going to create
	file >> height >> width >> textureRows >> textureColumns >> scale >> 
		xOffset >> yOffset >> depth >> gridScale;
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
void planeMap::draw()
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
void planeMap::toggleMap(){toggle = !toggle;}
void planeMap::initMapTextures()
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
void planeMap::initPlanePositions()
{
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			if(planes[y][x].plane != NULL)
			{
				D3DXVECTOR3 * pos = m_grid->getNode(y, x);
				pos->x += xOffset * scale;
				pos->y += yOffset * scale;
				pos->z = depth;
				planes[y][x].plane->setPosition(*pos);
			}
		}
	}
}
void planeMap::initPlaneScales()
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
float planeMap::getScale(){return scale;}
grid * planeMap::getGrid(){return m_grid;}
int planeMap::getWidth(){return width;}
int planeMap::getHeight(){return height;}

void planeMap::offsetMap(D3DXVECTOR3 offset)
{
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			if(planes[y][x].plane != NULL)
			{
				D3DXVECTOR3 * pos = planes[y][x].plane->getPosition();
				pos->x += offset.x;
				pos->y += offset.y;
				pos->z += offset.z;
			}
		}
	}
}