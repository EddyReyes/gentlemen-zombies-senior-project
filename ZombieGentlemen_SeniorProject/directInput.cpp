#include "directInput.h"

//#define debug
#ifndef debug


directInput::directInput(void)
{
	g_lpDI = NULL;
	g_lpDIDevice = NULL;
	hr = NULL;
}

directInput::~directInput(void)
{
}

/*******************************************************************
* Initialize Direct Input
*******************************************************************/
bool directInput::initDirectInput(HWND hwnd, HINSTANCE * hInst)
{
	// Create the DirectInput object. 
    hr = DirectInput8Create(*hInst, DIRECTINPUT_VERSION, 
                            IID_IDirectInput8, (void**)&g_lpDI, NULL); 

	if FAILED(hr) return FALSE; 

    // Retrieve a pointer to an IDirectInputDevice8 interface 
    hr = g_lpDI->CreateDevice(GUID_SysKeyboard, &g_lpDIDevice, NULL); 

	hr = g_lpDIDevice->SetDataFormat(&c_dfDIKeyboard); 

	if FAILED(hr) { 
		return FALSE; 
	} 

	// Set the cooperative level 
    hr = g_lpDIDevice->SetCooperativeLevel(hwnd, 
                             DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
    if FAILED(hr) 
    { 
        return FALSE; 
    } 

    // Get access to the input device. 
    hr = g_lpDIDevice->Acquire(); 
    if FAILED(hr) 
    { 
        return FALSE; 
    } 
}

void directInput::shutdownDirectInput(void)
{
	if (g_lpDI) 
    { 
        if (g_lpDIDevice) 
        { 
        // Always unacquire device before calling Release(). 
            g_lpDIDevice->Unacquire(); 
            g_lpDIDevice->Release();
            g_lpDIDevice = NULL; 
        } 
        g_lpDI->Release();
        g_lpDI = NULL; 
    }
}
#endif 