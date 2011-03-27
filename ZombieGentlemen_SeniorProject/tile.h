#pragma once
#include "dxManager.h"

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)
// pointer to pd3dDevice
#define pd3dDevice (*dxMgr->getDevice())

struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw;      // The untransformed, 3D position for the vertex
    DWORD color;        // The vertex color
};

class tile
{
private:
	LPDIRECT3DVERTEXBUFFER9 g_pVB; // Buffer to hold vertices 
	LPDIRECT3DTEXTURE9 image;	// image texture
	D3DXIMAGE_INFO * imageInfo;	// contains image parameters
	dxManager * dxMgr;

public:
	tile():g_pVB(NULL){}
	tile(dxManager * a_dxMgr, std::string filename)
	{
		g_pVB = NULL;
		dxMgr = a_dxMgr;
		imageInfo = new D3DXIMAGE_INFO();
		D3DXGetImageInfoFromFile(filename.c_str(), imageInfo);
		D3DXCreateTextureFromFile(pd3dDevice ,filename.c_str(),&image);
		SetupVB();
	}
	~tile()
	{
		g_pVB->Release();
	}

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
		{-1.0f, 1.0f,0.0f,  0.0f, 0.0f },
		{ 1.0f, 1.0f,0.0f,  1.0f, 0.0f },
		{-1.0f,-1.0f,0.0f,  0.0f, 1.0f },
		{ 1.0f,-1.0f,0.0f,  1.0f, 1.0f }
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
void setRenderStates()
{
	pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);
	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);
	pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void draw()
{
	D3DXMATRIX matScale;//, matTranslate, matWorld, matRotate;
	D3DXMatrixScaling(&matScale, 1.0f, 1.0f, 1.0f);
    pd3dDevice->SetTransform( D3DTS_WORLD, &matScale );

	// Set the current texture to use
	pd3dDevice->SetTexture( 0, image );
	// Set the vertex stream
	pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(CUSTOMVERTEX) );
    pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
	
	// draw the water
	pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,  0, 2 );
}
};