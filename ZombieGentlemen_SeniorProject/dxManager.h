/**
* dxManager handles the 2D graphics for our game
* status: running
*/

#pragma once

#define DIRECTINPUT_VERSION 0x0800
#define WINDOW_WIDTH 800
#define WINODW_HEIGHT 600

#include <d3d9.h>
#include <d3dx9tex.h>
#include <dinput.h>
#include <string>

struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw;      // The untransformed, 3D position for the vertex
    DWORD color;        // The vertex color
};

class dxManager
{
public:
	dxManager(void);
	~dxManager(void);
	bool initDirect3D(HWND * wndHandle, HINSTANCE * hInst);
	void shutdown(void);
	void beginRender(void);
	void endRender(void);
	IDirect3DSurface9* getSurfaceFromBitmap(std::string filename, int width, int height);
	IDirect3DSurface9* getAlphaSurfaceFromBitmap(std::string filename, int width, int height, D3DCOLOR ColorKey);
	IDirect3DSurface9* getBackBuffer(void);
	void blitToSurface(IDirect3DSurface9* srcSurface, const RECT *srcRect, const RECT *destRect);
	LPDIRECT3DDEVICE9 * getDevice(void);
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(int size, DWORD usage);
	void drawLine(int vertexIndex, int lineNum);
	HRESULT SetupVB(CUSTOMVERTEX * g_Vertices);

private:
	HRESULT                 lastResult;
	LPDIRECT3D9             pD3D;
	LPDIRECT3DDEVICE9       pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9 g_pVB; // Buffer to hold vertices
};
