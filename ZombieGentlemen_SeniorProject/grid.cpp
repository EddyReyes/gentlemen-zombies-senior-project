#include "grid.h"
//#define debug
//default constructor


grid::grid(){};

grid::grid(float a_gridScale , float a_XAxisLimit, float a_YAxisLimit, 
		   dxManager * a_dxMgr)
{
	// initialize grid data
	gridScale = a_gridScale;
	XAxisLimit = a_XAxisLimit;
	YAxisLimit = a_YAxisLimit;
	XLength = YAxisLimit/gridScale;
	YLength = XAxisLimit/gridScale;
	XAxis = YAxisLimit/2;
	YAxis = XAxisLimit/2;

	XLines = new LPD3DXLINE[XLength];
	YLines = new LPD3DXLINE[YLength];

	XlinesVertexList = new D3DXVECTOR2 * [XLength];
	YlinesVertexList = new D3DXVECTOR2 * [YLength];

	gridOn = false;
	dxMgr = a_dxMgr;
}
grid::~grid()
{
	releaseLines();
	releaseVertexLists();
}
void grid::toggleGrid()
{
	if(gridOn) gridOn = false;
	else gridOn = true;
}
void grid::initGrid()
{

	//Set X axis
	XlinesVertexList[0] =  new D3DXVECTOR2[2];
	XlinesVertexList[0][0] = D3DXVECTOR2(0.0f, XAxis);
	XlinesVertexList[0][1] = D3DXVECTOR2(XAxisLimit, XAxis);


	float tempIndex1, tempIndex2;
	tempIndex1 = 1;
	tempIndex2 = 1;
	// fill in X axis lines
	for(int i = 1; i < XLength; i++)
	{
		if(i < XLength/2)
		{
			XlinesVertexList[i] = new D3DXVECTOR2[2];
			XlinesVertexList[i][0] = D3DXVECTOR2(0.0f, XAxis+(gridScale*tempIndex1));
			XlinesVertexList[i][1] = D3DXVECTOR2(XAxisLimit, XAxis+(gridScale*tempIndex1));
			tempIndex1++;
		}
		else
		{
			XlinesVertexList[i] = new D3DXVECTOR2[2];
			XlinesVertexList[i][0] = D3DXVECTOR2(0.0f, XAxis-(gridScale*tempIndex2));
			XlinesVertexList[i][1] = D3DXVECTOR2(XAxisLimit, XAxis-(gridScale*tempIndex2));
			tempIndex2++;
		}
	}


	//Set Y axis
	YlinesVertexList[0] =  new D3DXVECTOR2[2];
	YlinesVertexList[0][0] = D3DXVECTOR2(YAxis, 0.0f);
	YlinesVertexList[0][1] = D3DXVECTOR2(YAxis, YAxisLimit);


	tempIndex1 = 1;
	tempIndex2 = 1;
		
	// fill in Y axis lines
	for(int i = 1; i < YLength; i++)
	{
		if(i < YLength/2)
		{
			YlinesVertexList[i] = new D3DXVECTOR2[2];
			YlinesVertexList[i][0] = D3DXVECTOR2(YAxis+(gridScale*tempIndex1), 0.0f);
			YlinesVertexList[i][1] = D3DXVECTOR2(YAxis+(gridScale*tempIndex1), YAxisLimit);
			tempIndex1++;
		}
		else
		{
			YlinesVertexList[i] = new D3DXVECTOR2[2];
			YlinesVertexList[i][0] = D3DXVECTOR2(YAxis-(gridScale*tempIndex2), 0.0f);
			YlinesVertexList[i][1] = D3DXVECTOR2(YAxis-(gridScale*tempIndex2), YAxisLimit);
			tempIndex2++;
		}
	}
	

 	for(int i = 0; i < XLength; i++)
	{
		D3DXCreateLine(*dxMgr->getDevice(), &XLines[i]);
	}
	for(int i = 0; i < YLength; i++)
	{
		D3DXCreateLine(*dxMgr->getDevice(), &YLines[i]);
	}
	
	XLines[0]->SetWidth(1.5);
	YLines[0]->SetWidth(1.5f);
}

void grid::drawGrid()
{
#ifndef debug
	if(gridOn)
	{
		// Draw the X axis
		/*const D3DXVECTOR2 lineVectorX[2] = 
			{XlinesVertexList[0][0], XlinesVertexList[0][1]};*/
		XLines[0]->Begin();
		XLines[0]->Draw(XlinesVertexList[0], 2, D3DCOLOR_ARGB(255 , 255, 255, 255));
		XLines[0]->End();

		// Draw the Y axis
		/*const D3DXVECTOR2 lineVectorY[2] = 
			{YlinesVertexList[0][0], YlinesVertexList[0][1]};*/
		YLines[0]->Begin();
		YLines[0]->Draw(YlinesVertexList[0], 2, D3DCOLOR_ARGB(255 , 255, 255, 255));
		YLines[0]->End();



		// draw the X lines
		for(int i = 1; i < XLength; i++)
		{
			/*const D3DXVECTOR2 lineVector[2] = 
			{XlinesVertexList[i][0], XlinesVertexList[i][1]};*/
			XLines[i]->Begin();
			XLines[i]->Draw(XlinesVertexList[i], 2, D3DCOLOR_ARGB(255 , 100, 100, 100));
			XLines[i]->End();
		}
		// draw the Y lines
		for(int i = 1; i < YLength; i++)
		{
			/*const D3DXVECTOR2 lineVector[2] = 
			{YlinesVertexList[i][0], YlinesVertexList[i][1]};*/
			YLines[i]->Begin();
			YLines[i]->Draw(YlinesVertexList[i], 2, D3DCOLOR_ARGB(255 , 100, 100, 100));
			YLines[i]->End();
		}
	}
#endif
}
bool grid::isGridOn(){return gridOn;}

void grid::changeGridScale(float a_gridScale)
{
	if(gridScale + a_gridScale > 1)
	{
		releaseLines();
		gridScale += a_gridScale;
		XLength = YAxisLimit/gridScale;
		YLength = XAxisLimit/gridScale;
		XLines = new LPD3DXLINE[XLength];
		YLines = new LPD3DXLINE[YLength];
		XlinesVertexList = new D3DXVECTOR2 * [XLength];
		YlinesVertexList = new D3DXVECTOR2 * [YLength];
		initGrid();
	}
}

void grid::releaseLines()
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
}

void grid::releaseVertexLists()
{
	delete [] XlinesVertexList;
	delete [] YlinesVertexList;
}