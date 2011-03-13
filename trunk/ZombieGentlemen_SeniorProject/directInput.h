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
	bool initDirectInput(HWND * hwnd, HINSTANCE * hInst);
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

/*******************************************************************
* Mouse Values
*******************************************************************/
/*
typedef struct DIMOUSESTATE
{
    LONG lX;
    LONG lY;
    LONG lZ;
    BYTE rgbButtons[4];
} DIMOUSESTATE, *LPDIMOUSESTATE;

Value				Description
LONG lX;			The change in X position.  If the mouse moves horizontally, 
					this value will store the amout of change.  0 is no change, 
					negative values are left movements and positive are right 
					movements.
LONG lY;			The change in Y position.  It is the same as X, but for vertical 
					movements.  0 is no change, negative values are upward movements 
					and positive values are downward movements.
LONG lZ;			The movement of the mouse wheel.  0, again, is no change, 
					negative values are downward movements and positive values 
					are upward movements.
BYTE rgbButtons[4];	This stores four values for buttons. Value 0 is the left 
					mouse-button, 1 is the right button, 2 is the middle button, 
					3 is the back button and 4 is the forward button.  
					These work exactly the way the 'keystate' array works.
*/

/*******************************************************************
* Key Values
*******************************************************************/
/*
Value				Description
DIK_ESCAPE			The Escape key
DIK_0 - 9			Numbers 0 though 9 on the main keyboard
DIK_MINUS			Minus key
DIK_EQUALS			Equals key
DIK_BACK			Backspace key
DIK_TAB				Tab key
DIK_A - Z			Letters A through Z, upper or lower case
DIK_LBRACKET		Left bracket key
DIK_RBRACKET		Right bracket key
DIK_RETURN			Enter on the main keyboard
DIK_LCONTROL		Left control key
DIK_RCONTROL		Right control key
DIK_LSHIFT			Left shift key
DIK_RSHIFT			Right shift key
DIK_LMENU			Left alt key
DIK_RMENU			Right alt key
DIK_SPACE			Spacebar
DIK_F1 - F15		Function keys 1 through 15
DIK_NUMPAD0 - 9		Numeric keypad keys 0 through 9
DIK_ADD				'+' key on numeric keypad
DIK_NUMPADENTER		Enter key on numeric keypad
DIK_HOME			Home key (not on numeric keypad)
DIK_END				End key (not on numeric keypad)
DIK_PRIOR			Page Up key (not on numeric keypad)
DIK_NEXT			Page Down key (not on numeric keypad)
DIK_UP				Up arrow key (not on numeric keypad)
DIK_DOWN			Down arrow key (not on numeric keypad)
DIK_LEFT			Left arrow key (not on numeric keypad)
DIK_RIGHT			Right arrow key (not on numeric keypad)
DIK_INSERT			Insert key (not on numeric keypad)
DIK_DELETE			Delete key (not on numeric keypad)
*/