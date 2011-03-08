#include <stdio.h>
// include Windows header file thats needed for all Windows applications
#include <Windows.h>

/*******************************************************************************************************
* Windows
* The following code creates a window
********************************************************************************************************/


HINSTANCE hInst; // global handle to hold the application instance
HWND wndHandle; //global variable to hold the window handle

// forward declarations
bool initWindow( HINSTANCE hInstance) ;
LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );

// This is winmain, the main entry point for Windows applications
int WINAPI WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					LPTSTR lpCmdLine, int nCmdShow )
{
	//Initialize the window
	if (!initWindow( hInstance ) )
		return false;

	//main message loop
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );
	
	while (GetMessage(&msg, NULL, 0, 0) )
	{
		TranslateMessage ( &msg );
		DispatchMessage( &msg );
	}
}

/*********************************************************************
* gool initWindow( HINSTANCE hInstance )
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

/*******************************************************************************************************
* Direct X
* The following code initializes Direct X
********************************************************************************************************/

//IDirect3D9 *Direct3DCreate9( D3D_SDK_VERSION );