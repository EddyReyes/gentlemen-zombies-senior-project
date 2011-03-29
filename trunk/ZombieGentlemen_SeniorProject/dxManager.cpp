/**
* see dxManager.h for details
*/

#include ".\dxmanager.h"


dxManager::dxManager(void)
{
	pD3D = NULL;
 	pd3dDevice = NULL;
	lastResult = NULL;
}

dxManager::~dxManager(void)
{
}


/*******************************************************************
* Initialize Direct3D
*******************************************************************/
bool dxManager::initDirect3D(HWND * wndHandle, HINSTANCE * hInst)
{
	if( NULL == ( pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
		lastResult = E_FAIL;
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount  = 1;
	d3dpp.BackBufferHeight = WINDOW_HEIGHT;
	d3dpp.BackBufferWidth  = WINDOW_WIDTH;
	d3dpp.hDeviceWindow    = *wndHandle;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;

    if( FAILED( pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, *wndHandle,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &pd3dDevice ) ) )
    {
		lastResult = E_FAIL;
        return false;
    }

	pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	// set render states for vertex buffers
	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);
	pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// return true if everything inititalized correctly
	return true;
}

void dxManager::shutdown(void)
{
    if( pd3dDevice != NULL) 
	{
        pd3dDevice->Release();
		pd3dDevice = NULL;
	}
    if( pD3D != NULL)
	{
        pD3D->Release();
		pD3D = NULL;
	}
}

void dxManager::beginRender()
{
	if( NULL == pd3dDevice )
        return;

    // Clear the backbuffer to a black color
    pd3dDevice->Clear( 0, NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
	pd3dDevice->BeginScene();
}

void dxManager::endRender(void)
{
	pd3dDevice->EndScene();
	// Present the backbuffer contents to the display
    pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

IDirect3DSurface9* dxManager::getSurfaceFromBitmap(std::string filename, int width, int height)
{
	HRESULT hResult;
	IDirect3DSurface9* surface = NULL;

	hResult = pd3dDevice->CreateOffscreenPlainSurface(width, height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);
	if (FAILED(hResult))
		return NULL;

	hResult = D3DXLoadSurfaceFromFile(surface, NULL, NULL, filename.c_str(), NULL, D3DX_DEFAULT, 0, NULL);
	if (FAILED(hResult))
		return NULL;

	return surface;
}
IDirect3DSurface9* dxManager::getAlphaSurfaceFromBitmap(std::string filename, int width, int height, D3DCOLOR ColorKey)
{
	HRESULT hResult;
	IDirect3DSurface9* surface = NULL;

	hResult = pd3dDevice->CreateOffscreenPlainSurface(width, height, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);
	if (FAILED(hResult))
		return NULL;

	hResult = D3DXLoadSurfaceFromFile(surface, NULL, NULL, filename.c_str(), NULL, D3DX_DEFAULT, ColorKey, NULL);
	if (FAILED(hResult))
		return NULL;

	return surface;
}

IDirect3DSurface9* dxManager::getBackBuffer(void)
{
	IDirect3DSurface9* backbuffer = NULL;

	if (!pd3dDevice)
		return NULL;

	HRESULT hResult = pd3dDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	if (FAILED(hResult))
		return NULL;
	else
		return backbuffer;
}

void dxManager::blitToSurface(IDirect3DSurface9* srcSurface, const RECT *srcRect, const RECT *destRect)
{
	pd3dDevice->StretchRect(srcSurface, srcRect, getBackBuffer(), destRect, D3DTEXF_NONE);
}

LPDIRECT3DDEVICE9 * dxManager::getDevice(void)
{
	return &pd3dDevice;
}