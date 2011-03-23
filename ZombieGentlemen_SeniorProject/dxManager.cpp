/**
* see dxManager.h for details
*/

#include ".\dxmanager.h"


dxManager::dxManager(void)
{
	pD3D = NULL;
 	pd3dDevice = NULL;
	lastResult = NULL;
	g_pVB = NULL;
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
	d3dpp.BackBufferHeight = WINODW_HEIGHT;
	d3dpp.BackBufferWidth  = WINDOW_WIDTH;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.hDeviceWindow    = *wndHandle;

    if( FAILED( pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, *wndHandle,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &pd3dDevice ) ) )
    {
		lastResult = E_FAIL;
        return false;
    }

	// Turn on the zbuffer
	pd3dDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );

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
    pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
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

LPDIRECT3DVERTEXBUFFER9 dxManager::createVertexBuffer(int size, DWORD usage)
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

void dxManager::drawLine(int vertexIndex, int lineNum)
{
	pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(CUSTOMVERTEX) );
    pd3dDevice->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE);
	pd3dDevice->DrawPrimitive( D3DPT_LINESTRIP, vertexIndex, lineNum);
}

HRESULT  dxManager::SetupVB(CUSTOMVERTEX * g_Vertices)
{
	HRESULT hr;

	// Create the vertex buffer
	g_pVB = createVertexBuffer(sizeof(g_Vertices), D3DFVF_XYZRHW|D3DFVF_DIFFUSE);

    // Fill the vertex buffer.
    VOID* pVertices;
	
	hr = g_pVB->Lock( 0, sizeof(g_Vertices), (void**)&pVertices, 0 );
	if FAILED (hr)
        return E_FAIL;

	// copy the vertices into the buffer
    memcpy( pVertices, g_Vertices, sizeof(g_Vertices) );

	// unlock the vertex buffer
    g_pVB->Unlock();

    return hr;
}