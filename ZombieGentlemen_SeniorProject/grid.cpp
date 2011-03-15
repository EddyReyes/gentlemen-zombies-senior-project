#include "grid.h"
//#define debug
//default constructor
grid::grid(){};

grid::grid(float a_gridScale , float a_XAxisLimit, float a_YAxisLimit, 
		   dxManager * a_dxMgr)
{
	gridScale = a_gridScale;
	XAxisLimit = a_XAxisLimit;
	YAxisLimit = a_YAxisLimit;
	XLength = YAxisLimit/gridScale;
	YLength = XAxisLimit/gridScale;
	XLines = new LPD3DXLINE[XLength];
	YLines = new LPD3DXLINE[YLength];
	XlinesVertexList = new D3DXVECTOR2 * [XLength];
	YlinesVertexList = new D3DXVECTOR2 * [YLength];
	gridOn = false;
	dxMgr = a_dxMgr;
}
grid::~grid()
{
	for(int i = 0; i < XLength; i++)
	{
		XLines[i]->Release();
	}
	for(int i = 0; i < YLength; i++)
	{
		YLines[i]->Release();
	}
	delete [] XLines;
	delete [] YLines;
	delete [] XlinesVertexList;
	delete [] YlinesVertexList;
}
void grid::toggleGrid()
{
	if(gridOn) gridOn = false;
	else gridOn = true;
}
void grid::initGrid()
{
	float tempIndex;
	// fill in X axis lines
	for(int i = 0; i < XLength; i++)
	{
		tempIndex = (float)i;
		XlinesVertexList[i] = new D3DXVECTOR2[2];
		XlinesVertexList[i][0] = D3DXVECTOR2(0.0f, (gridScale*tempIndex));
		XlinesVertexList[i][1] = D3DXVECTOR2(XAxisLimit, (gridScale*tempIndex));
	}

	// fill in Y axis lines
	for(int i = 0; i < YLength; i++)
	{
		tempIndex = (float)i;
		YlinesVertexList[i] = new D3DXVECTOR2[2];
		YlinesVertexList[i][0] = D3DXVECTOR2((gridScale*tempIndex), 0.0f);
		YlinesVertexList[i][1] = D3DXVECTOR2((gridScale*tempIndex), YAxisLimit);
	}
	

 	for(int i = 0; i < XLength; i++)
	{
		D3DXCreateLine(*dxMgr->getDevice(), &XLines[i]);
	}
	for(int i = 0; i < YLength; i++)
	{
		D3DXCreateLine(*dxMgr->getDevice(), &YLines[i]);
	}

}
void grid::drawGrid()
{
#ifndef debug
	if(gridOn)
	{
		// draw the X axis
		for(int i = 0; i < XLength; i++)
		{
			const D3DXVECTOR2 lineVector[2] = 
			{XlinesVertexList[i][0], XlinesVertexList[i][1]};
			XLines[i]->Begin();
			XLines[i]->Draw(lineVector, 2, D3DCOLOR_ARGB(255 , 255, 255, 255));
			XLines[i]->End();
		}
		// draw the Y axis
		for(int i = 0; i < YLength; i++)
		{
			const D3DXVECTOR2 lineVector[2] = 
			{YlinesVertexList[i][0], YlinesVertexList[i][1]};
			YLines[i]->Begin();
			YLines[i]->Draw(lineVector, 2, D3DCOLOR_ARGB(255 , 255, 255, 255));
			YLines[i]->End();
		}
	}
#endif
}
bool grid::isGridOn(){return gridOn;}