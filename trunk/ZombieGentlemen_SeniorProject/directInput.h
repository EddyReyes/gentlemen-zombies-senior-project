#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

class directInput
{
public:
	directInput(void);
	~directInput(void);
	bool initDirectInput(HWND * hwnd, HINSTANCE * hInst);
	void shutdownDirectInput(void);

private:
	LPDIRECTINPUT8        g_lpDI;	// the direct input object
	LPDIRECTINPUTDEVICE8  g_lpDIDevice; // the direct input device
	HRESULT hr;
};