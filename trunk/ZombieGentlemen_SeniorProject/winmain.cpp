// includeFiles.h holds all other include headers nessary for this game
#include "includeFiles.h"
#include <d3d9.h>
#include <d3dx9tex.h>

/*******************************************************************************************************
* Windows
* The following code creates a window
********************************************************************************************************/

HINSTANCE hInstance; // global handle to hold the application instance
HWND wndHandle; //global variable to hold the window handle

// forward declarations
bool initWindow( HINSTANCE hInstance);
LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );

// This is winmain, the main entry point for Windows applications
int WINAPI WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					LPTSTR lpCmdLine, int nCmdShow )
{
	//Initialize the window
	if (!initWindow(hInstance))
	{
		MessageBox(NULL, "Unable to create window", "ERROR", MB_OK);
		return false;
	}
	
	// Create DirectX Manager
	dxManager *dxMgr = new dxManager();

	// Initialzie DirectX Manager
	if(!dxMgr->initDirect3D(wndHandle, &hInstance))
	{
		MessageBox(NULL, "Unable to initialize Direct3D", "ERROR", MB_OK);
		return false;
	}

	// Direct Input
	directInput * inputMgr = new directInput();

	// initialize Direct Input
	if(!inputMgr->initDirectInput(wndHandle, hInstance))
	{
		MessageBox(NULL, "Unable to initialize Direct Input", "ERROR", MB_OK);
		return false;
	}

	//Sound Manager
	sound soundMgr(&wndHandle);
	soundMgr.initDirectSound(wndHandle);
	//Load sound (filename, bufferID) in this case the first buffer is 0
	soundMgr.LoadSound("Combat music.wav", 0);
	//SetVolume(bufferID, Volume)
	soundMgr.SetVolume(0, 0);
	// incriment the volume by 100, 50 times
	/*for(int i = 0; i < 100; i++)
		soundMgr.incrimentVolume(0);*/
	//play sound playSound(bufferID) in this case the first buffer is 0
	soundMgr.playSound(0);
	BYTE * buffer; 
	DIMOUSESTATE mouseState;

#define KEYDOWN(name, key) (name[key] & 0x80) 
#define BUTTONDOWN(name, key) (name.rgbButtons[key] & 0x80) 

	enum { K_LEFT_ARROW = 0,
		K_UP_ARROW,
		K_DOWN_ARROW,
		K_RIGHT_ARROW };
	enum { NONE=0,
	   M_LEFT_ARROW,
	   M_RIGHT_ARROW,
	   CIRCLE};
	IDirect3DSurface9* arrows = dxMgr->getSurfaceFromBitmap("arrows.bmp",192, 48);
	IDirect3DSurface9* mouseArrow = dxMgr->getSurfaceFromBitmap("mousearrows.bmp",192, 48);
	RECT src;
	RECT spriteSrc;
	RECT spriteDest;
	LONG curX;
	LONG curY;
	// set the starting point for the circle sprite
	curX = 320;
	curY = 240;

	src.left = src.right = src.top =0; src.bottom = 48;
	src.right = src.left + 48;

	RECT screen;
	screen.left = 0;
	screen.right = 48;
	screen.top = 0;
	screen.bottom = 48;


	//main message loop
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	// Game/Windows loop
	/*while (GetMessage(&msg, NULL, 0, 0) )
	{
		TranslateMessage ( &msg );
		DispatchMessage( &msg );
	}*/
	
	while( msg.message!=WM_QUIT )
	{
	
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage ( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			inputMgr->reAcquireDevices();
			inputMgr->updateKeyboardState(); 
			buffer = inputMgr->getKeyboardState();
			inputMgr->updateMouseState();
			mouseState = *(inputMgr->getMouseState());

			src.top = 0;
			src.bottom = 48;

			// keyboard
				

			if(buffer[DIK_ESCAPE] & 0x80)
			{
				PostQuitMessage(0);
			}

			if (KEYDOWN(buffer, DIK_LEFT))
			{
				src.left = (48 * K_LEFT_ARROW);
				if(screen.left>0 && screen.right>48)
				{
					screen.left -=5;
					screen.right -=5;
				}
			}
			else if (KEYDOWN(buffer, DIK_UP))
			{
				src.left = (48 * K_UP_ARROW);
				if(screen.top>0 && screen.bottom>48)
				{
					screen.top-=5;
					screen.bottom-=5;
				}
			}
			else if (KEYDOWN(buffer, DIK_DOWN))
			{
				src.left = (48 * K_DOWN_ARROW);
				if(screen.bottom < 480 && screen.top < (480-50))
				{
					screen.bottom +=5;
					screen.top+=5;
				}
			}
			else if (KEYDOWN(buffer, DIK_RIGHT))
			{
				src.left = (48 * K_RIGHT_ARROW);
				if(screen.right < 650 && screen.left < (670-60))
				{
					screen.right +=5;
					screen.left +=5;
				}
			}

			src.right = src.left + 48;


			// mouse

			if (BUTTONDOWN(mouseState, 0))
				src.left = (48 * M_LEFT_ARROW);
			if (BUTTONDOWN(mouseState, 1))
				src.left = (48 * M_RIGHT_ARROW);

			src.right = src.left + 48;

			// CIRCLE SPRITE
			// set the source rectangle
			spriteSrc.top = 0;
			spriteSrc.bottom = spriteSrc.top + 48;
			spriteSrc.left = (48 * CIRCLE);
			spriteSrc.right = spriteSrc.left + 48;
			// set the destination rectangle
			spriteDest.top = curY;
			spriteDest.left = curX;
			spriteDest.right = spriteDest.left + 48;
			spriteDest.bottom = spriteDest.top + 48;

			curX += mouseState.lX;
			curY += mouseState.lY;

			//g.draw	
			// call our render function
			dxMgr->beginRender();

			dxMgr->blitToSurface(mouseArrow, &src, NULL);

			// blit the sprite to the back buffer
			dxMgr->blitToSurface(mouseArrow, &spriteSrc, &spriteDest);

			// blit this letter to the back buffer
			dxMgr->blitToSurface(arrows, &src, &screen);

			dxMgr->endRender();
		}

	}
}

/*********************************************************************
* bool initWindow( HINSTANCE hInstance )
* initWindow registers the window calss for the application. creates the window
**********************************************************************/
bool initWindow( HINSTANCE hInstance )
{
	WNDCLASSEX wcex;

	// Fill the WNDCLASSEX structure. This describes how the window ill look to the system
	wcex.cbSize			= sizeof(WNDCLASSEX);		// the sixe of the structure
	wcex.style			= CS_HREDRAW | CS_VREDRAW;  // the class style
	wcex.lpfnWndProc	= (WNDPROC)WndProc;			// the window procedure callback
	wcex.cbClsExtra		= 0;						// extra bytes to allocate for this class
	wcex.cbWndExtra		= 0;						// extra bytes to allocate for this instance
	wcex.hInstance		= hInstance;				// handle to the application instance
	wcex.hIcon			= 0;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW); // the default cursor
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1); // the background color
	wcex.lpszMenuName	= NULL;						// the resource name for the menu
	wcex.lpszClassName	= "GSP Senior Project";			// the class name being created
	wcex.hIconSm		= 0;						// the handle to the small icon
	RegisterClassEx(&wcex);

	// Create the window
	wndHandle = CreateWindow(
				"GSP Senior Project",		// the window class to use
				"GSP Senior Project",		// the title bar text
				WS_OVERLAPPEDWINDOW,	// the window style
				CW_USEDEFAULT,			// the starting x coordinate
				CW_USEDEFAULT,			// the startying y coordinate
				640,					// the pixel width of the window
				480,					// the pizel height of the window
				NULL,					// the parent windo; NULL for desktop
				NULL,					// The menu for the application; NULL for none
				hInstance,				// the handle to the applicatilon instance
				NULL);					// no values passed to the window

	// make sure that the window handle that is created is valid
	if(!wndHandle)
		return false;

	// Display the window on the screen
	ShowWindow(wndHandle, SW_SHOW);
	UpdateWindow(wndHandle);
	return true;
}

/***************************************************************************
* LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
*
* The window procedure
****************************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Check any available message from the queue 
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	// Always return the message to the default window
	// procedure for further processing
	return DefWindowProc(hWnd, message, wParam, lParam);
}