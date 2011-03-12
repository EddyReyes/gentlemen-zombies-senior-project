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
	void reAcquireDevices();

private:
	LPDIRECTINPUT8        g_lpDI;	// the pointer to our DirectInput interface
	LPDIRECTINPUTDEVICE8  g_lpDIKeyboard; // the pointer to the keyboard device
	LPDIRECTINPUTDEVICE8  g_lpDIMouse; // the pointer to the mouse device
	HRESULT hr;
	BYTE keyState[256]; // the storage for the key-information
	DIMOUSESTATE mouseState; // the storage for the mouse-information
};