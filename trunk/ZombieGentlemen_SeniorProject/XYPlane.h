#pragma once
#include "dxManager.h"

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)
// pointer to pd3dDevice
#define pd3dDevice (*dxMgr->getDevice())

struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw;      // The untransformed, 3D position for the vertex
    float tu, tv;        // The vertex color
};
struct FloatRect
{
	float right, left, bottom, top;
};

class XYPlane
{
private:
	LPDIRECT3DVERTEXBUFFER9 g_pVB; // Buffer to hold vertices 
	LPDIRECT3DTEXTURE9 image;	// image texture
	D3DXIMAGE_INFO * imageInfo;	// contains image parameters
	D3DXVECTOR3 * position; // vector holding x, y, and z location parameters
	float width, height, scale; 
	FloatRect * textureCoord; // structure containing UV coordinate data
	dxManager * dxMgr; // pointer to dxMgr
	int Columns, Rows; // number of columns and rows in sprite sheet
	bool imageOn; // toogle for drawing XYPlane
	bool sharingImage; // keeps track of weather the image is being shared with another object

public:
	/*************************************************************************
	* XYPlane
	* default constructor
	* does nothing, nothing at all, move along now
	*************************************************************************/
	XYPlane(){};
	/*************************************************************************
	* XYPlane
	* constructor
	* sets up all the variables to a default value
	* This constructor creates a new image in memory for the passed in file
	*************************************************************************/
	XYPlane(dxManager * a_dxMgr, std::string filename)
	{
		g_pVB = NULL;
		dxMgr = a_dxMgr;
		imageInfo = new D3DXIMAGE_INFO();
		setImage(filename);
		// set up position
		position = new D3DXVECTOR3(0,0,0);
		// set up size
		width = 1.0f;
		height = 1.0f;
		// set up scale
		scale = 1.0f;
		// set up texture coordinates
		textureCoord = new FloatRect;
		setTextureCoordinates(0, 1, 0, 1);
		// set up vertex buffer
		//SetupVB(); called inside setTextureCoordinates

		//set up rows and columns
		Columns = 1; 
		Rows = 1;
		// set up image toggle
		imageOn = true;
		sharingImage = false;
	}
	/*************************************************************************
	* XYPlane
	* constructor
	* sets up all the variables to a default value
	* This constructor is for use when sharing an image with another object
	*************************************************************************/
	XYPlane(dxManager * a_dxMgr, LPDIRECT3DTEXTURE9 * a_image, D3DXIMAGE_INFO * a_imageInfo)
	{
		g_pVB = NULL;
		dxMgr = a_dxMgr;
		// set pointer to shared image
		image = *a_image;
		// set pointer to image info
		imageInfo = a_imageInfo;
		// set up position
		position = new D3DXVECTOR3(0,0,0);
		// set up size
		width = 1.0f;
		height = 1.0f;
		// set up scale
		scale = 1.0f;
		// set up texture coordinates
		textureCoord = new FloatRect;
		setTextureCoordinates(0, 1, 0, 1);
		// set up vertex buffer
		//SetupVB(); called inside setTextureCoordinates

		//set up rows and columns
		Columns = 1; 
		Rows = 1;
		// set up image toggle
		imageOn = true;
		sharingImage = true;
	}
	/*************************************************************************
	* ~XYPlane
	* destructor
	* releases vertex buffer from memory
	* also releases image if it is not being shared
	*************************************************************************/
	~XYPlane()
	{
		releaseImage();
		if(g_pVB != NULL)
			g_pVB->Release(); // release vertex buffer
	}
	/*************************************************************************
	* ~releaseImage
	* checks if image is being shared and then releases image if it is not
	*************************************************************************/
	void releaseImage()
	{ 
		if(!sharingImage)
		{
			if(image != NULL)
			{
				image->Release(); // release image if not being shared
			}
		}
	}
	/*************************************************************************
	* setImage
	* loads image into LPDIRECT3DTEXTURE9 image
	* retrieves file information from image and stores in D3DXIMAGE_INFO * imageInfo
	*************************************************************************/
	void setImage(std::string filename)
	{
		D3DXCreateTextureFromFile(pd3dDevice, filename.c_str(),&image);
		D3DXGetImageInfoFromFile(filename.c_str(), imageInfo);
		sharingImage = false;
	}
	/*************************************************************************
	* setParam
	* set the position of the vertex buffer (upper left corner) in world space
	* and set the size of the vertex buffer in world coordinate units
	*************************************************************************/
	void setParam(float a_x, float a_y, float a_z, float a_width, float a_height)
	{
		setPosition(a_x, a_y, a_z);
		setSize(a_width, a_height);
	}
	void setParam(D3DXVECTOR3 a_position, float a_width, float a_height)
	{
		setPosition(a_position);
		setSize(a_width, a_height);
	}
	/*************************************************************************
	* setPosition
	* set the position of the vertex buffer (upper left corner) in world space
	*************************************************************************/
	void setPosition(float a_x, float a_y, float a_z)
	{
		position->x = a_x;
		position->y = a_y;
		position->z = a_z;
	}
	void setPosition(D3DXVECTOR3 a_position)
	{
		position->x = a_position.x;
		position->y = a_position.y;
		position->z = a_position.z;
	}
	/*************************************************************************
	* setSize
	* set the size of the image in world coordinate units
	*************************************************************************/
	void setSize(float a_width, float a_height)
	{
		width = a_width;
		height = a_height;
		SetupVB();
	}
	/*************************************************************************
	* setScale
	* set the scale of the vertex buffer for rendering
	*************************************************************************/
	void setScale(float a_scale)
	{
		scale = a_scale;
		//width *= a_scale;
		//height *= a_scale;
	}
	/*************************************************************************
	* setTextureCoordinates
	* manually set the UV texture coordinates
	*************************************************************************/
	void setTextureCoordinates(float a_top, float a_bottom, float a_left, float a_right)
	{
		textureCoord->top = a_top;
		textureCoord->bottom = a_bottom;
		textureCoord->left = a_left;
		textureCoord->right = a_right;
		SetupVB();
	}
	/*************************************************************************
	* setImageRowsColumns, setRows, setColumns
	* set the rows and columns of images in the texture
	*************************************************************************/
	void setImageRowsColumns(int a_Rows, int a_Columns)
	{
		Rows = a_Rows;
		Columns = a_Columns; 
	}
	void setRows(int a_Rows){Rows = a_Rows;}
	void setColumns(int a_Columns){Columns = a_Columns;}

	/*************************************************************************
	* selectTextureSource
	* sets the UV coordinates to a specific rectangle inside the image
	*************************************************************************/
	void selectTextureSource(int a_Row, int a_Column)
	{
		if(a_Row >= Rows || a_Column >= Columns)
		{
			MessageBox(NULL, "Invalid texture source called", "ERROR", MB_OK);
		}
		else
		{
			textureCoord->top =  ((imageInfo->Height/Rows) * a_Row) / (float)imageInfo->Height;
			textureCoord->bottom = (((imageInfo->Height/Rows) * a_Row) + imageInfo->Height/Rows) / (float)imageInfo->Height;
			textureCoord->left = ( a_Column * (imageInfo->Width/Columns)) / (float)imageInfo->Width;
			textureCoord->right = ((a_Column * (imageInfo->Width/Columns)) + (imageInfo->Width/Columns)) / (float)imageInfo->Width;
		}
		SetupVB();
	}
	LPDIRECT3DTEXTURE9 * getTexture(){return &image;}
	D3DXIMAGE_INFO * getImageInfo(){return imageInfo;}

	void toggleImage(){imageOn = imageOn?false:true;}

	/*************************************************************************
	* SetupVB
	* Setup the vertex buffer
	*************************************************************************/
	HRESULT SetupVB()
	{
		HRESULT hr;

		// Initialize three vertices for rendering a triangle
		CUSTOMVERTEX g_Vertices[] =
		{
			//Sets up verticies from position and down the y axis

			//// upper left corner
			//{ position->x, position->y, 0.0f,  textureCoord->left, textureCoord->top},
			////upper right corner
			//{ (position->x + width), position->y, 0.0f, textureCoord->right, textureCoord->top},
			//// lower left corner
			//{ position->x, (position->y - height), 0.0f,  textureCoord->left, textureCoord->bottom},
			//// lower right corner
			//{ (position->x + width), (position->y - height), 0.0f,  textureCoord->right, textureCoord->bottom}

			// upper left corner
			{ 0.0f, 0.0f, 0.0f,  textureCoord->left, textureCoord->top},
			//upper right corner
			{ width, 0.0f, 0.0f, textureCoord->right, textureCoord->top},
			// lower left corner
			{ 0.0f, -1 * height, 0.0f,  textureCoord->left, textureCoord->bottom},
			// lower right corner
			{ width, -1 * height, 0.0f,  textureCoord->right, textureCoord->bottom}
		};


		// Create the vertex buffer
		g_pVB = createVertexBuffer(sizeof(g_Vertices) * sizeof(CUSTOMVERTEX), D3DFVF_CUSTOMVERTEX);

		// Fill the vertex buffer.
		VOID* pVertices;

		hr = g_pVB->Lock( 0, sizeof(g_Vertices), (void**)&pVertices, 0 );
		if FAILED (hr)
			return E_FAIL;

		// copy the vertices into the buffer
		memcpy( pVertices, g_Vertices, sizeof(g_Vertices) );

		// unlock the vertex buffer
		g_pVB->Unlock();

		return S_OK;
	}
	/*************************************************************************
	* createVertexBuffer
	* creates the vertexbuffer
	*************************************************************************/
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(int size, DWORD usage)
	{
		HRESULT hr;
		LPDIRECT3DVERTEXBUFFER9 buffer;

		// Create the vertex buffer.

		hr = pd3dDevice->CreateVertexBuffer( size,
			0, 
			usage,
			D3DPOOL_DEFAULT, 
			&buffer, 
			NULL );
		if FAILED ( hr)
			return NULL;

		return buffer;
	}
	/*************************************************************************
	* setRenderStates
	* sets the render states for the vertex buffer to utilize alpha blending if needed
	*************************************************************************/
	void setRenderStates()
	{
		//pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);
		pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);
		pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	/*************************************************************************
	* draw
	* draws the vertex buffer into the world space, with the texture attached to it
	* also translates, and scales the vertex buffer before drawing
	*************************************************************************/
	void draw()
	{
		if(imageOn)
		{
			D3DXMATRIX matScale, matTranslate, matWorld;//, matRotate;

			D3DXMatrixScaling(&matScale, scale, scale, scale); // set scale
			D3DXMatrixTranslation(&matTranslate, position->x, position->y, position->z); // move to position
			D3DXMatrixMultiply(&matWorld, &matScale, &matTranslate); 
			pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

			// Set the current texture to use
			pd3dDevice->SetTexture( 0, image );
			// Set the vertex stream
			pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(CUSTOMVERTEX) );
			pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );

			// draw the water
			pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,  0, 2 );
		}
	}
};