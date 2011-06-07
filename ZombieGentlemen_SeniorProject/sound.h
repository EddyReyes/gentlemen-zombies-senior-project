/**
* sound is a class which handles Direct Sound
* a sound object holds a total of 10 sound buffers
* or you could think of them as 10 channels on a mixer
* each one of these channels has its own corresponding volume and pan
* each one of these is manipulated individualy through class methods
* and each channel is identified by a number between 0 and 9

status: running
wish list: mute toggle method for each indidual channel
		   mute toggle method for entire sound mixer
*/


#pragma once
#include <dsound.h>
#include "dsutil.h"
#include <iostream>
#include "stringArray.h"
using namespace std;

enum soundList{ // this is the list of in game sounds
	soundMenu,
	soundLevel, 
	soundWalk,
	soundJump1,
	soundJump2,
	soundArmorJump1,
	soundArmorJump2,
	soundArmorLose1,
	soundArmorPickup1,
	soundArmorPickup2,
	soundDeath1,
	soundDeath2,
	soundDeath3,
	soundQuote1,
	soundQuote2,
	soundQuote3,
	soundQuote4,
	soundQuote5,
	soundCheckPoint
};
class sound
{
private:
	LPDIRECTSOUND8        g_pDS;	// The DirectSound Device
	HWND * wndHandle;   // a pointer to the windows handle
	LPDIRECTSOUNDBUFFER * SoundChannel; // pointer to an array of ten buffers for sound.
	int * ChannelVolume; // pointer to an array of 10 volume values
	int * ChannelPan; // pointer to an array of 10 Pan Values
	stringArray * soundFiles;

	// private methods
	void initializeChannelVolume(int initVolume, int numChannels);
	void initializeChannelPan(int initPan, int numChannels);

public:

	sound();
	~sound();
	LPDIRECTSOUNDBUFFER LoadWaveToSoundBuffer(std::string wavFilename);
	bool LoadSound(std::string wavFilename, int bufferID);
	void SetVolume(int bufferID, int Volume);
	void incrimentVolume(int bufferID);
	void decrimentVolume(int bufferID);
	void SetPan(int bufferID, int Pan);
	void incrimentPan(int bufferID);
	void decrimentPan(int bufferID);
	bool playSound(int bufferID);
	bool playSoundLoop(int bufferID);
	bool stopSound(int bufferID);
	bool initDirectSound(HWND * a_wndHandle);
	void shutdownDirectSound(void);
	void initSoundFiles(std::string initFiles);

};
