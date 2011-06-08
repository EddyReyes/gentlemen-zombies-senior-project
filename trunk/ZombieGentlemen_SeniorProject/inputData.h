#pragma once
#include "directInput.h"

#define xControllerTimout 3

struct inputData
{
	BYTE * keystate;
	int * keyLag;
	DIMOUSESTATE mouseState;
	XboxController * xcont;
	bool xConnected;
	float xConnectTimer;

	void init(XboxController * a_xcont)
	{
		xcont = a_xcont;
		xConnected = false;
		xConnectTimer = xControllerTimout+1;
		// initialize key lag data
		keyLag = new int [256];
		for(int i = 0; i < 256; i++){keyLag[i] = 0;}
	}
};