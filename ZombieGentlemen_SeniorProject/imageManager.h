#include "dxManager.h"
#include <stdio.h>
#include <fstream>
#include <ctype.h>
#include <string.h>

// pointer to pd3dDevice
#define pd3dDevice (*dxMgr->getDevice())

class imageManager
{
private:
	LPDIRECT3DTEXTURE9 * images;	// image texture
	D3DXIMAGE_INFO ** imageInfo;	// contains image parameters
	char ** textFile;
	dxManager * dxMgr;
	int fileHeight, fileWidth, arraySize;

public:
	imageManager()
	{
		images = NULL;
		imageInfo = NULL;
		textFile = NULL;
		dxMgr = NULL;
		fileHeight = 0;
		fileWidth = 0;
		arraySize = 0;
	}
	~imageManager()
	{
		// destroy all images
		for(int y  = 0; y < fileHeight; y ++)
		{
			if(images[y] != NULL)
			{
				images[y]->Release();
				delete images[y];
				images[y] = NULL;
			}
		}
		delete [] images;
		// destroy all imageInfo
		for(int y  = 0; y < fileHeight; y ++)
		{
			if(imageInfo[y] != NULL)
			{
				ZeroMemory(imageInfo[y], sizeof(D3DXIMAGE_INFO));
				delete imageInfo[y];
				imageInfo[y] = NULL;
			}
		}
		delete [] imageInfo;
		// destroy 2D array of characters
		if(textFile)
		{
			for(int i = 0; i < fileHeight; i++)
			{
				delete [] textFile[i];
			}
			delete [] textFile;
			textFile = NULL;
		}
	}
	void initImageManager(char * filename, dxManager * a_dxMgr)
	{
		dxMgr = a_dxMgr;
		loadTextFile(filename);
		initImagesArray();
		loadImages();
	}
	void loadTextFile(char * filename)
	{
		fstream file(filename);
		// capture the height(number of rows) and width(number of chars)
		file >> fileHeight >> fileWidth;
		// use height to create the respective rows required
		textFile = new char * [fileHeight];
		// loop through array and create collumns and assign NULL to all chars
		for(int y = 0; y < fileHeight; y++){
			textFile[y] = new char [fileWidth];
			for(int x = 0; x < fileWidth; x++)
			{textFile[y][x] = NULL;}
		}
		// get the data from the file into the 2D array
		int c;
		bool newLine = false;
		for(int y = 0; y < fileHeight; ++y){
			newLine = false;
			for(int x = 0; x < fileWidth && !newLine; ++x){
				c = file.get();
				newLine = false;
				if(c == '\n' || c == '\r'){
					x--;
					newLine = true;
				}
				else{
					textFile[y][x] = c;
				}
			}
		}
	}

	void initImagesArray()
	{
		// find size necessary to fill in array
		for(int y = 0; y < fileHeight && textFile[y][0] !=  NULL; y++)
		{arraySize++;}
		// create an array of the right size for image pointers
		images = new LPDIRECT3DTEXTURE9 [arraySize];
		for(int i = 0; i < arraySize; i++)
		{images[i] = NULL;} // fill all image pointers with NULL
		// create an array of the right size for imageInfo pointers
		imageInfo = new D3DXIMAGE_INFO * [arraySize];
		for(int i = 0; i < arraySize; i++)
		{imageInfo[i] = NULL;} // zero out the imageInfo struct
	}

	void loadImages()
	{
		// create a string to hold the file name characters
		std::string str;
		// loop through 2D char array
		for(int y = 0; y < fileHeight && textFile[y][0] !=  NULL; y++)
		{
			// loop through array row to get each character
			// will exit loop if the next character is NULL
			for(int x = 0; x < fileWidth && textFile[y][x] !=  NULL; x++)
			{
				str.push_back(textFile[y][x]); // add characters from 2D char array to string
			}
			// after the string has collected characters from row the file name has
			// been captured in the string, and it can be used to load an image
			// file into memory, and the file info can be captured
			D3DXCreateTextureFromFile(pd3dDevice, str.c_str(), &(images[y]));
			D3DXGetImageInfoFromFile(str.c_str(), imageInfo[y]);
			// the string is cleared for use with the next row of characters
			str.clear();
		}
	}
	LPDIRECT3DTEXTURE9 * getImage(int index)
	{
		// check if the index is out of bounds
		if(index < 0 || index > arraySize)
		{return NULL;} // if out of bounds return NULL
		// if index is within memory bounds return a pointer
		else{return &(images[index]);}
	}
	D3DXIMAGE_INFO * getImageInfo(int index)
	{
		// check if the index is out of bounds
		if(index < 0 || index > arraySize)
		{return NULL;} // if out of bounds return NULL
		// if index is within memory bounds return a pointer
		else{return imageInfo[index];}
	}
};
