#pragma once
#include "dxManager.h"

#define pd3dDevice (*dxMgr->getDevice())

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
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, WINDOW_WIDTH/WINDOW_HEIGHT, nearClip, farClip);
		pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
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
			&D3DXVECTOR3(0.0f, 1.0f, 0.0f)); //Up Direction

		pd3dDevice->SetTransform(D3DTS_VIEW, &matView);
	}
	/*************************************************************************
	* updateCamera
	* updates the camera according to member parameters
	*************************************************************************/
	void updateCamera()
	{
		createCamera(1.0f, 750.0f);
		moveCamera(cameraPosition);
		pointCamera(cameraLook);
		pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	}
	/*************************************************************************
	* updateCamera3D
	* sets new parameters for teh camera in all 3 Dimensions
	*************************************************************************/
	void updateCamera3D(D3DXVECTOR3 cameraMove, D3DXVECTOR3 cameraPoint)
	{
		cameraPosition = cameraMove;
		cameraLook = cameraPoint;
		updateCamera();
	}
	/*************************************************************************
	* SetupCamera2D
	* sets new parameters for teh focusing only on the XY plane
	*************************************************************************/
	void SetupCamera2D(float a_X, float a_Y, float a_Z)
	{
		cameraPosition = D3DXVECTOR3(a_X, a_Y, a_Z);
		cameraLook = D3DXVECTOR3(a_X, a_Y, 0.0f);
		updateCamera();
	}
	/*************************************************************************
	* SetHudCamera
	* Sets up the orthographic projection for the hud
	*************************************************************************/
	void SetHudCamera ()
	{
		D3DXMATRIX Ortho2D;
		D3DXMATRIX Identity;

		D3DXMatrixOrthoLH(&Ortho2D, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 1.0f);
		D3DXMatrixIdentity(&Identity);

		pd3dDevice->SetTransform(D3DTS_PROJECTION, &Ortho2D);
		pd3dDevice->SetTransform(D3DTS_WORLD, &Identity);
		pd3dDevice->SetTransform(D3DTS_VIEW, &Identity);
	}
	/*************************************************************************
	* moveCameraPos functions
	* moves the camera position on the corrisponding axis
	*************************************************************************/
	void moveCameraPosX(float move)
	{
		cameraPosition.x += move;
	}
	void moveCameraPosY(float move)
	{
		cameraPosition.y += move;
	}
	void moveCameraPosZ(float move)
	{
		cameraPosition.z += move;
	}
	/*************************************************************************
	* moveCameraPoint functions
	* moves the camera pointing vector on the corrisponding axis
	*************************************************************************/
	void moveCameraPointX(float move)
	{
		cameraLook.x += move;
	}
	void moveCameraPointY(float move)
	{
		cameraLook.y += move;
	}
	void moveCameraPointZ(float move)
	{
		cameraLook.z += move;
	}
	/*************************************************************************
	* moveOnXAxis
	* moves the camera position and point on the X plane simultaniously
	*************************************************************************/
	void moveOnXAxis(float move)
	{
		moveCameraPosX(move);
		moveCameraPointX(move);
	}
	/*************************************************************************
	* moveOnYAxis
	* moves the camera position and point on the Y plane simultaniously
	*************************************************************************/
	void moveOnYAxis(float move)
	{
		moveCameraPosY(move);
		moveCameraPointY(move);
	}
	/*************************************************************************
	* moveOnZAxis
	* moves the camera position and point on the Z plane simultaniously
	* for 2D game it is not recomended this function be used, instead use moveCameraPosZ
	*************************************************************************/
	void moveOnZAxis(float move)
	{
		moveCameraPosZ(move);
		moveCameraPointZ(move);
	}
};