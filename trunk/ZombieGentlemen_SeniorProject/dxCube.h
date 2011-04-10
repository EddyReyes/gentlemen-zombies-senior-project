#pragma once
#include "dxManager.h"
#include "CustomVertex.h"

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)
// pointer to pd3dDevice
#define pd3dDevice (*dxMgr->getDevice())

class dxCube
{
private:
	LPDIRECT3DVERTEXBUFFER9 g_pVB; // Buffer to hold vertices 
	LPDIRECT3DTEXTURE9 image;	// image texture
	D3DXIMAGE_INFO * imageInfo;	// contains image parameters
	D3DXVECTOR3 * position; // vector holding x, y, and z location parameters
	float width, height, depth, scale; 
	FloatRect * textureCoord; // structure containing UV coordinate data
	dxManager * dxMgr; // pointer to dxMgr
	int Columns, Rows; // number of columns and rows in sprite sheet
	bool cubeToggle; // toogle for drawing XYPlane
	bool sharingImage; // keeps track of weather the image is being shared with another object
	bool transparencyCulling;
	float origin;

	// private member functions
	HRESULT SetupVB();
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(int size, DWORD usage);

public:
	// constructors
	dxCube();
	dxCube(dxManager * a_dxMgr, std::string filename);
	dxCube(dxManager * a_dxMgr, LPDIRECT3DTEXTURE9 * a_image, D3DXIMAGE_INFO * a_imageInfo);

	// destructors
	~dxCube();
	void releaseImage();

	// member functions
	void setRenderStates();
	void draw();

	// mutators
	void setImage(std::string filename);
	void shareImage(LPDIRECT3DTEXTURE9 * a_image, D3DXIMAGE_INFO * a_imageInfo);
	void setParam(float a_x, float a_y, float a_z, float a_width, float a_height, float a_depth);
	void setParam(D3DXVECTOR3 a_position, float a_width, float a_height, float a_depth);
	void setPosition(float a_x, float a_y, float a_z);
	void setPosition(D3DXVECTOR3 a_position);
	void setSize(float a_width, float a_height, float a_depth);
	void setScale(float a_scale);
	void setTextureCoordinates(float a_top, float a_bottom, float a_left, float a_right);
	void setImageRowsColumns(int a_Rows, int a_Columns);
	void setRows(int a_Rows);
	void setColumns(int a_Columns);
	void selectTextureSource(int a_Row, int a_Column);

	// toggle
	void toggleCube();
	void toggleCubeOff();
	void toggleCubeOn();
	void toggleTransparencyCulling();

	// accessors
	LPDIRECT3DTEXTURE9 * getTexture();
	D3DXIMAGE_INFO * getImageInfo();
	float getXPosition();
	float getYPosition();
	float getZPosition();
	D3DXVECTOR3 * getPosition();
	float getWidth();
	float getHeight();
	float getDepth();
	float getScale();
};