#pragma once
#include <dsound.h>
#include "dsutil.h"
#include <iostream>
using namespace std;

class sound
{
private:
	LPDIRECTSOUND8        g_pDS;	// The DirectSound Device: Dont really know what this is for but it is important.
	HWND * wndHandle;

public:

	sound(HWND * a_wndHandle)
	{
		wndHandle = a_wndHandle;
	};

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
	* playSound
	* plays a sound currently in a buffer only once
	*******************************************************************/
	void playSound(LPDIRECTSOUNDBUFFER whichBuffer)
	{
		whichBuffer->Play( 0, 0, 0);
	}

	/*******************************************************************
	* playSoundLoop
	* plays a sound in a buffer repeatedly
	*******************************************************************/
	void playSoundLoop(LPDIRECTSOUNDBUFFER whichBuffer)
	{
		whichBuffer->Play( 0, 0, DSBPLAY_LOOPING );
	}

	/*******************************************************************
	* stopSound
	* stops the sound in this buffer from playing
	*******************************************************************/
	void stopSound(LPDIRECTSOUNDBUFFER whichBuffer)
	{
		whichBuffer->Stop();
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
	void shutdownDirectSound(void);

};