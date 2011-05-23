#pragma once
#include "directInput.h"
struct inputData
{
	BYTE * keystate;
	int * keyLag;
	DIMOUSESTATE mouseState;
	XboxController * xcont;

	void init(XboxController * a_xcont)
	{
		xcont = a_xcont;
		// initialize key lag data
		keyLag = new int [256];
		for(int i = 0; i < 256; i++){keyLag[i] = 0;}
	}
};