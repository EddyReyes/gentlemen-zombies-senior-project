#include "imageManager.h"

imageManager::imageManager()
{
	images = NULL;
	imageInfo = NULL;
	fileNames = NULL;
	dxMgr = NULL;
	size = 0;
}
imageManager::~imageManager()
{
	// destroy all images
	for(int y  = 0; y < size; y ++)
	{
		if(images[y] != NULL)
		{
			(*images[y])->Release();
			delete images[y];
			images[y] = NULL;
		}
	}
	delete [] images;
	// destroy all imageInfo
	for(int y  = 0; y < size; y ++)
	{
		if(imageInfo[y] != NULL)
		{
			ZeroMemory(imageInfo[y], sizeof(D3DXIMAGE_INFO));
			delete imageInfo[y];
			imageInfo[y] = NULL;
		}
	}
	delete [] imageInfo;
	
	// destroy array of strings
	if(fileNames) fileNames->~stringArray();
	fileNames = NULL;
}
void imageManager::initImageManager(char * filename, dxManager * a_dxMgr)
{
	dxMgr = a_dxMgr;
	loadTextFile(filename);
	initImagesArray();
	loadImages();
}
void imageManager::loadTextFile(char * filename)
{
	fileNames = new stringArray();
	fileNames->loadFromTextFile(filename);
	size = fileNames->getSize();
}

void imageManager::initImagesArray()
{
	// create an array of the right size for image pointers
	images = new LPDIRECT3DTEXTURE9 * [size];
	for(int i = 0; i < size; i++)
	{images[i] = new LPDIRECT3DTEXTURE9;} 
	// create an array of the right size for imageInfo pointers
	imageInfo = new D3DXIMAGE_INFO * [size];
	for(int i = 0; i < size; i++)
	{imageInfo[i] =  new D3DXIMAGE_INFO;}
}

void imageManager::loadImages()
{
	// loop through size
	for(int y = 0; y < size; y++)
	{
		// load file name from string array
		std::string * str = fileNames->getStringPtrAt(y);
		// load texture from file in file name array
		D3DXCreateTextureFromFile(pd3dDevice, str->c_str(),images[y]);
		// laod image info from file in file name array
		D3DXGetImageInfoFromFile(str->c_str(), imageInfo[y]);
	}
}

LPDIRECT3DTEXTURE9 * imageManager::getImage(int index)
{
	// check if the index is out of bounds
	if(index < 0 || index > size)
	{return NULL;} // if out of bounds return NULL
	// if index is within memory bounds return a pointer
	else{return images[index];}
}
D3DXIMAGE_INFO * imageManager::getImageInfo(int index)
{
	// check if the index is out of bounds
	if(index < 0 || index > size)
	{return NULL;} // if out of bounds return NULL
	// if index is within memory bounds return a pointer
	else{return imageInfo[index];}
}
int imageManager::getSize(){return size;}