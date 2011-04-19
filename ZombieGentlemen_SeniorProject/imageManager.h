#pragma once
#include "dxManager.h"
#include "stringArray.h"

// pointer to pd3dDevice
#ifndef pd3dDevice
#define pd3dDevice (*dxMgr->getDevice())
#endif

class imageManager
{
private:
	LPDIRECT3DTEXTURE9 ** images;	// image texture
	D3DXIMAGE_INFO ** imageInfo;	// contains image parameters
	stringArray * fileNames;
	dxManager * dxMgr;
	int size;

	// private member functions
	void loadTextFile(char * filename);
	void initImagesArray();
	void loadImages();

public:
	imageManager();
	~imageManager();
	void initImageManager(char * filename, dxManager * a_dxMgr);
	LPDIRECT3DTEXTURE9 * getImage(int index);
	D3DXIMAGE_INFO * getImageInfo(int index);
};
