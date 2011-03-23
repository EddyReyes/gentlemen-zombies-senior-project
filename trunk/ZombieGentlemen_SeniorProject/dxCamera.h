#pragma once
#include "dxManager.h"
#define WINDOW_WIDTH 800
#define WINODW_HEIGHT 600

class dxCamera
{
private:
	D3DXMATRIX matView;					// the view matrix
	D3DXMATRIX matProj;					// the projection matrix
	D3DXVECTOR3 cameraPosition;			// the position of the camera
	D3DXVECTOR3 cameraLook;				// where the camera is pointing
	dxManager * dxMgr;

public:
	
	// constructor
	dxCamera(dxManager * a_dxMgr)
	{
		dxMgr = a_dxMgr;
		// functions to create the camera
		createCamera(1.0f, 750.0f); // near clip plane, far clip plane
		cameraPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		cameraLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		moveCamera(cameraPosition);
		pointCamera(cameraLook);
	}
	// destructor
	~dxCamera(){};

/*************************************************************************
* createCamera
* creates a virtual camera
*************************************************************************/
void createCamera(float nearClip, float farClip)
{
	//Here we specify the field of view, aspect ratio and near and far clipping planes.
    D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, WINDOW_WIDTH/WINODW_HEIGHT, nearClip, farClip);
    (*dxMgr->getDevice())->SetTransform(D3DTS_PROJECTION, &matProj);
}

/*************************************************************************
* moveCamera
* moves the camera to a position specified by the vector passed as a 
* parameter
*************************************************************************/
void moveCamera(D3DXVECTOR3 vec)
{
	cameraPosition = vec;
}

/*************************************************************************
* pointCamera
* points the camera a location specified by the passed vector
*************************************************************************/
void pointCamera(D3DXVECTOR3 vec)
{
	cameraLook = vec;

	D3DXMatrixLookAtLH(&matView, &cameraPosition,	//Camera Position
                                 &cameraLook,		//Look At Position
                                 &D3DXVECTOR3(0.0f, 1.0f, 0.0f));		//Up Direction

	(*dxMgr->getDevice())->SetTransform(D3DTS_VIEW, &matView);
}

/*************************************************************************
* updateCamera
* sets new parameters for teh camera
*************************************************************************/
void updateCamera(D3DXVECTOR3 cameraMove, D3DXVECTOR3 cameraPoint)
{
	cameraPosition = cameraMove;
	cameraLook = cameraPoint;
	createCamera(1.0f, 750.0f);
	moveCamera(cameraPosition);
	pointCamera(cameraLook);
	(*dxMgr->getDevice())->SetTransform(D3DTS_PROJECTION, &matProj);
}

};