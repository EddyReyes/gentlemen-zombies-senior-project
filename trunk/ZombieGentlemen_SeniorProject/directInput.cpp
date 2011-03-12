/**
* see directInput.h for details
*/

#include "directInput.h"

directInput::directInput(void)
{
	g_lpDI = NULL;
	g_lpDIKeyboard = NULL;
	g_lpDIMouse =NULL;
	hr = NULL;
}

directInput::~directInput(void)
{
}

/*******************************************************************
* Initialize Direct Input
*******************************************************************/
bool directInput::initDirectInput(HWND wndHandle, HINSTANCE hInst)
{
	// Create the DirectInput object. 
    hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, 
                            IID_IDirectInput8, (void**)&g_lpDI, NULL); 

	// Debuging
	if FAILED(hr) return FALSE; 
	if(hr == DIERR_INVALIDPARAM)
		MessageBox(NULL, "*** DirectInput8Create() FAILED *** Invalid Params", "ERROR", MB_OK);
		else if(hr == DIERR_BETADIRECTINPUTVERSION)
		MessageBox(NULL, "*** DirectInput8Create() FAILED *** Beta Direct Input Version", "ERROR", MB_OK);
		else if(hr == DIERR_OLDDIRECTINPUTVERSION)
		MessageBox(NULL, "*** DirectInput8Create() FAILED *** Old Direct Input Version", "ERROR", MB_OK);
		else if(hr == DIERR_OUTOFMEMORY)
		MessageBox(NULL, "*** DirectInput8Create() FAILED *** Out of Memory", "ERROR", MB_OK);
	if FAILED(hr) return FALSE; 

    // Retrieve a pointer to an IDirectInputDevice8 interface 
    hr = g_lpDI->CreateDevice(GUID_SysMouse, &g_lpDIMouse, NULL); 
	hr = g_lpDIMouse->SetDataFormat(&c_dfDIMouse); 

	hr = g_lpDI->CreateDevice(GUID_SysKeyboard, &g_lpDIKeyboard, NULL); 
	hr = g_lpDIKeyboard->SetDataFormat(&c_dfDIKeyboard); 


	if FAILED(hr) { 
		return FALSE; 
	} 

	// Set the cooperative level 
    hr = g_lpDIMouse->SetCooperativeLevel(wndHandle, 
                             DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
	// Set the cooperative level 
    hr = g_lpDIKeyboard->SetCooperativeLevel(wndHandle, 
                             DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 

    if FAILED(hr) 
    { 
        return FALSE; 
    } 

    // Get access to the input device. 
    hr = g_lpDIKeyboard->Acquire(); 
	hr = g_lpDIMouse->Acquire();
	
    if FAILED(hr) 
    { 
        return FALSE; 
    } 
}

void directInput::shutdownDirectInput(void)
{
	if (g_lpDI) 
    { 
		if (g_lpDIMouse) 
        { 
        // Always unacquire device before calling Release(). 
            g_lpDIMouse->Unacquire(); 
            g_lpDIMouse->Release();
            g_lpDIMouse = NULL; 
        } 
        if (g_lpDIKeyboard) 
        { 
        // Always unacquire device before calling Release(). 
            g_lpDIKeyboard->Unacquire(); 
            g_lpDIKeyboard->Release();
            g_lpDIKeyboard = NULL; 
        } 
        g_lpDI->Release();
        g_lpDI = NULL; 
    }
}