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
using namespace std;


class sound
{
private:
	LPDIRECTSOUND8        g_pDS;	// The DirectSound Device
	HWND * wndHandle;   // a pointer to the windows handle
	LPDIRECTSOUNDBUFFER * SoundChannel; // pointer to an array of ten buffers for sound.
	int * ChannelVolume; // pointer to an array of 10 volume values
	int * ChannelPan; // pointer to an array of 10 Pan Values

public:

	sound(HWND * a_wndHandle)
	{
		// initialize windows handle for use with sound class
		wndHandle = a_wndHandle;
		
		// initialize array of 10 buffers
		SoundChannel = new LPDIRECTSOUNDBUFFER[10];
		ChannelVolume = new int [10];
		ChannelPan = new int [10];
		initializeChannelVolume(-5000);
		initializeChannelPan(0);
	};

	// Initialize ChannelVolume array
	void initializeChannelVolume(int initVolume)
	{
		for(int i = 0; i < 10; i++)
		{
			ChannelVolume[i] = initVolume;
		}
	}

	// Initialize ChannelPan array
	void initializeChannelPan(int initPan)
	{
		for(int i = 0; i < 10; i++)
		{
			ChannelPan[i] = initPan;
		}
	}

	/*******************************************************************
	* LoadWaveToSoundBuffer
	* Loads a wave file into a DirectSound Buffer
	*******************************************************************/
	LPDIRECTSOUNDBUFFER LoadWaveToSoundBuffer(std::string wavFilename)
	{
		LPDIRECTSOUNDBUFFER apDSBuffer = NULL;
		CWaveFile *wavFile;
		HRESULT hr;

		wavFile = new CWaveFile();
		wavFile->Open((char*)wavFilename.c_str(), NULL, WAVEFILE_READ );
		if( wavFile->GetSize() == 0 )
		{
			MessageBox(*wndHandle, "invalid file", "ERROR", MB_OK);
			return false;
		}

		DSBUFFERDESC dsbd;
		ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
		dsbd.dwSize          = sizeof(DSBUFFERDESC);
		dsbd.dwFlags         = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN;
		dsbd.dwBufferBytes   = wavFile->GetSize();
		dsbd.guid3DAlgorithm = GUID_NULL;
		dsbd.lpwfxFormat     = wavFile->m_pwfx;

		hr = g_pDS->CreateSoundBuffer( &dsbd, &apDSBuffer, NULL );
		if FAILED (hr)
		{
			MessageBox(NULL, "unable to create sound buffer", "ERROR", MB_OK);
			return NULL;
		}

		VOID*   pDSLockedBuffer      = NULL; // Pointer to locked buffer memory
		DWORD   dwDSLockedBufferSize = 0;    // Size of the locked DirectSound buffer
		DWORD   dwWavDataRead        = 0;    // Amount of data read from the wav file 
		
		hr = apDSBuffer->Lock( 0, wavFile->GetSize(), 
							   &pDSLockedBuffer, &dwDSLockedBufferSize, 
							   NULL, NULL, 0L );
		if FAILED (hr)
			return NULL;

		// Reset the wave file to the beginning 
		wavFile->ResetFile();

		// Read the wave file
		hr = wavFile->Read( (BYTE*) pDSLockedBuffer,
						   dwDSLockedBufferSize, 
						   &dwWavDataRead );
		// Check to make sure that this was successful
		if FAILED (hr)
			return NULL;

		// Check to make sure the wav file is not empty
		if( dwWavDataRead == 0 )
		{
			// Wav is blank, so just fill with silence
			FillMemory( (BYTE*) pDSLockedBuffer, 
						dwDSLockedBufferSize, 
						(BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0 ) );
		}
		else if( dwWavDataRead < dwDSLockedBufferSize )
		{
			// Don't repeat the wav file, just fill in silence 
			FillMemory( (BYTE*) pDSLockedBuffer + dwWavDataRead, 
					   dwDSLockedBufferSize - dwWavDataRead, 
					   (BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0 ) );
		}

		// Unlock the buffer, we don't need it anymore.
		apDSBuffer->Unlock( pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0 );

		// Clean up
		delete wavFile;

		return apDSBuffer;
	}

	/*******************************************************************
	* LoadSound(string, int)
	* Loads a wave file into a specific DirectSound Buffer
	*******************************************************************/
	bool LoadSound(std::string wavFilename, int bufferID)
	{
		// Check if bufferID is a valid (between 0 and 10)
		if(bufferID >= 10 || bufferID < 0) return false;

		SoundChannel[bufferID] = LoadWaveToSoundBuffer(wavFilename);
		return true;
	}

	/*******************************************************************
	* SetVolume(bufferID, Volume)
	* Sets the volume for a specific DirectSound Buffer
	* Volume must be a level between -10000 and 0
	* -10000 being the lowest, 0 being the highest
	*******************************************************************/
	void SetVolume(int bufferID, int Volume)
	{
		if(Volume < 0 || Volume >= -1000){

			ChannelVolume[bufferID] = Volume;
			SoundChannel[bufferID]->SetVolume(ChannelVolume[bufferID]);
		}
	}

	/*******************************************************************
	* incrimentVolume(int bufferID)
	* incriment any buffer channel volume by 100 to max value of 0
	*******************************************************************/
	void incrimentVolume(int bufferID)
	{
		if(ChannelVolume[bufferID] < 0)
			ChannelVolume[bufferID] += 100;
		if(ChannelVolume[bufferID] > 0)
			ChannelVolume[bufferID] = 0;
		SoundChannel[bufferID]->SetVolume(ChannelVolume[bufferID]);
	}

	/*******************************************************************
	* decrimentVolume(int bufferID)
	* decriment any buffer channel volume by 100 to min value of -10000
	*******************************************************************/
	void decrimentVolume(int bufferID)
	{
		if(ChannelVolume[bufferID] > -10000)
			ChannelVolume[bufferID] -= 100;
		if(ChannelVolume[bufferID] < -10000)
			ChannelVolume[bufferID] = -10000;
		SoundChannel[bufferID]->SetVolume(ChannelVolume[bufferID]);
	}

	/*******************************************************************
	* SetPan(bufferID, Pan)
	* Sets the pan for a specific DirectSound Buffer
	* Pan must be a level between -10000 and 10000
	* -10000 being the lowest, 10000 being the highest
	*******************************************************************/
	void SetPan(int bufferID, int Pan)
	{
		if(Pan <= 10000 || Pan >= -1000)
			SoundChannel[bufferID]->SetPan(Pan);
	}

	/*******************************************************************
	* incrimentPan(int bufferID)
	* incriment any buffer channel pan by 100 to max value of 10000
	*******************************************************************/
	void incrimentPan(int bufferID)
	{
		if(ChannelPan[bufferID] < 10000)
			ChannelPan[bufferID] += 100;
		if(ChannelPan[bufferID] > 10000)
			ChannelPan[bufferID] = 10000;
		SoundChannel[bufferID]->SetPan(ChannelPan[bufferID]);
	}

	/*******************************************************************
	* decrimentPan(int bufferID)
	* decriment any buffer channel pan by 100 to min value of -1000
	*******************************************************************/
	void decrimentPan(int bufferID)
	{
		if(ChannelPan[bufferID] > -10000)
			ChannelPan[bufferID] -= 100;
		if(ChannelPan[bufferID] < -10000)
			ChannelPan[bufferID] = -10000;
		SoundChannel[bufferID]->SetPan(ChannelPan[bufferID]);
	}


	/*******************************************************************
	* playSound
	* plays a sound currently in a buffer only once
	*******************************************************************/
	bool playSound(int bufferID)
	{
		// Check if bufferID is a valid (between 0 and 10)
		if(bufferID >= 10 || bufferID < 0) return false;

		SoundChannel[bufferID]->Play( 0, 0, 0);
		return true;
	}

	/*******************************************************************
	* playSoundLoop
	* plays a sound in a buffer repeatedly
	*******************************************************************/
	bool playSoundLoop(int bufferID)
	{
		// Check if bufferID is a valid (between 0 and 10)
		if(bufferID >= 10 || bufferID < 0) return false;

		SoundChannel[bufferID]->Play( 0, 0, DSBPLAY_LOOPING);
		return true;
	}

	/*******************************************************************
	* stopSound
	* stops the sound in this buffer from playing
	*******************************************************************/
	bool stopSound(int bufferID)
	{
		// Check if bufferID is a valid (between 0 and 10)
		if(bufferID >= 10 || bufferID < 0) return false;

		SoundChannel[bufferID]->Stop();
		return true;
	}
	/*******************************************************************
	* initDirectSound
	* Initializes DirectSound
	*******************************************************************/
	bool initDirectSound(HWND hwnd)
	{
		HRESULT hr;

		hr = DirectSoundCreate8( NULL, &g_pDS, NULL );
		if FAILED (hr)
			return false;

		// Set DirectSound cooperative level 
		hr = g_pDS->SetCooperativeLevel( hwnd, DSSCL_PRIORITY );
		if FAILED ( hr )
			return false;

		return true;
	}

	/*******************************************************************
	* shutdownDirectSound
	* Releases the DirecSound device
	*******************************************************************/
	void shutdownDirectSound(void)
	{
		if (g_pDS)
		{
			g_pDS->Release();
			g_pDS = NULL;
		}
	}
};
