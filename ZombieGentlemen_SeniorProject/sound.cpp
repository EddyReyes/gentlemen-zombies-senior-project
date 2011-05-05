/**
* see sound.h for details
*/


#pragma once
#include "sound.h"

sound::sound()
{
	// initialize array of 10 buffers
	SoundChannel = new LPDIRECTSOUNDBUFFER[10];
	ChannelVolume = new int [10];
	ChannelPan = new int [10];
	initializeChannelVolume(-5000, 10);
	initializeChannelPan(0, 10);
};

// Create a sound object with a custom number of channels
sound::sound(std::string file, int numChannels)
{
	// initialize array of 10 buffers
	SoundChannel = new LPDIRECTSOUNDBUFFER[numChannels];
	ChannelVolume = new int [numChannels];
	ChannelPan = new int [numChannels];
	initSoundFiles(file);
	initializeChannelVolume(-5000, numChannels);
	initializeChannelPan(0, numChannels);

};

// Initialize ChannelVolume array
void sound::initializeChannelVolume(int initVolume, int numChannels)
{
	for(int i = 0; i < numChannels; i++)
	{
		ChannelVolume[i] = initVolume;
	}
}

// Initialize ChannelPan array
void sound::initializeChannelPan(int initPan, int numChannels)
{
	for(int i = 0; i < numChannels; i++)
	{
		ChannelPan[i] = initPan;
	}
}

/*******************************************************************
* LoadWaveToSoundBuffer
* Loads a wave file into a DirectSound Buffer
*******************************************************************/
LPDIRECTSOUNDBUFFER sound::LoadWaveToSoundBuffer(std::string wavFilename)
{
	LPDIRECTSOUNDBUFFER apDSBuffer = NULL;
	CWaveFile *wavFile;
	HRESULT hr;

	wavFile = new CWaveFile();
	wavFile->Open((char*)wavFilename.c_str(), NULL, WAVEFILE_READ );
	if( wavFile->GetSize() == 0 )
	{
		MessageBox(*wndHandle, "invalid file", "Direct Sound Error", MB_OK);
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
		MessageBox(NULL, "unable to create sound buffer", "Direct Sound Error", MB_OK);
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
bool sound::LoadSound(std::string wavFilename, int bufferID)
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
void sound::SetVolume(int bufferID, int Volume)
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
void sound::incrimentVolume(int bufferID)
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
void sound::decrimentVolume(int bufferID)
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
void sound::SetPan(int bufferID, int Pan)
{
	if(Pan <= 10000 || Pan >= -1000)
		SoundChannel[bufferID]->SetPan(Pan);
}

/*******************************************************************
* incrimentPan(int bufferID)
* incriment any buffer channel pan by 100 to max value of 10000
*******************************************************************/
void sound::incrimentPan(int bufferID)
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
void sound::decrimentPan(int bufferID)
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
bool sound::playSound(int bufferID)
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
bool sound::playSoundLoop(int bufferID)
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
bool sound::stopSound(int bufferID)
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
bool sound::initDirectSound(HWND * a_wndHandle)
{
	HRESULT hr;
	wndHandle = a_wndHandle;

	hr = DirectSoundCreate8( NULL, &g_pDS, NULL );
	if FAILED (hr)
		return false;

	// Set DirectSound cooperative level 
	hr = g_pDS->SetCooperativeLevel( *wndHandle, DSSCL_PRIORITY );
	if FAILED ( hr )
		return false;

	return true;
}

/*******************************************************************
* shutdownDirectSound
* Releases the DirecSound device
*******************************************************************/
void sound::shutdownDirectSound(void)
{
	if (g_pDS)
	{
		g_pDS->Release();
		g_pDS = NULL;
	}
	delete [] SoundChannel; // delete channels
	delete [] ChannelVolume; // delete all volume variables
	delete [] ChannelPan; // delete all pan vairables
}
void sound::initSoundFiles(std::string initFiles)
{
	soundFiles = new stringArray();
	soundFiles->loadFromTextFile(initFiles);
	LoadSound(soundFiles->getStringAt(0), 0);
}