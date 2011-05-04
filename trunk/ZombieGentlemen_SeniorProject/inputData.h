#pragma once

struct inputData
{
	BYTE * keystate;
	int * keyLag;
	DIMOUSESTATE mouseState;

	void init()
	{
		// initialize key lag data
		keyLag = new int [256];
		for(int i = 0; i < 256; i++){keyLag[i] = 0;}
	}
};