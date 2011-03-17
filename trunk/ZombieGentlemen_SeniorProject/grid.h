#include "dxManager.h"
#include "object.h"

class grid
{
private:
	LPD3DXLINE * XLines;
	LPD3DXLINE * YLines;
	D3DXVECTOR2 ** XlinesVertexList;
	D3DXVECTOR2 ** YlinesVertexList;
	float XAxisLimit, YAxisLimit;
	bool gridOn;
	dxManager * dxMgr;
	float gridScale;
	int YLength, XLength;
	void releaseLines();
	void releaseVertexLists();
	
	//Axis Parameters
	float XAxis, YAxis;

	XY ** nodes;

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