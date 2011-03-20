#include "dxManager.h"
#include "object.h"

#define debug
class grid
{
private:

	#ifndef debug

	LPD3DXLINE * XLines;
	LPD3DXLINE * YLines;
	D3DXVECTOR2 ** XlinesVertexList;
	D3DXVECTOR2 ** YlinesVertexList;
	float XAxisLimit, YAxisLimit;

	
	float gridScale;
	int YLength, XLength;
	
	
	
	//Axis Parameters
	float XAxis, YAxis;

	
	#endif
	// pixel to represent line
	IDirect3DSurface9* line;
	// rectangles to represent locations for drawing
	RECT lineRect;
	RECT lineRectScreen;
	
	bool gridOn;
	
	// nodes
	XY ** nodes;
	XY * center;

	void releaseLines();
	void releaseVertexLists();
	dxManager * dxMgr;
public:
	grid();
	grid(float a_gridScale , float a_XAxisLimit, float a_YAxisLimit, dxManager * a_dxMgr);
	~grid();
	void initGrid();
	void toggleGrid();
	void drawGrid();
	bool isGridOn();
	void changeGridScale(float a_gridScale);
};