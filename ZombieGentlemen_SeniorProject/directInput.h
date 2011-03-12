/**
* directInput handles the input for DirectX
* status: running
*/

#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

class directInput
{
public:
	directInput(void);
	~directInput(void);
	bool initDirectInput(HWND hwnd, HINSTANCE hInst);
	bool updateMouseState();
	bool updateKeyboardState();
	BYTE * getKeyboardState();
	DIMOUSESTATE * getMouseState();
	void shutdownDirectInput(void);

private:
	LPDIRECTINPUT8        g_lpDI;	// the direct input object
	LPDIRECTINPUTDEVICE8  g_lpDIKeyboard; // the direct input Keybaord
	LPDIRECTINPUTDEVICE8  g_lpDIMouse; // the direct input Keybaord
	HRESULT hr;
	BYTE keyState[256]; // all keystates will be held in this array
	DIMOUSESTATE mouseState; // mouse state
};