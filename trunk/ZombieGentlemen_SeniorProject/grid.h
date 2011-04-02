#include "dxManager.h"
#include "object.h"

#define debug
#ifndef debug
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
	
	bool gridOn;
	
	// nodes
	D3DXVECTOR2 ** nodes;
	D3DXVECTOR2 * center;

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
#endif

class grid
{
private:
	D3DXVECTOR3 ** nodes;
	int rows, columns;
	float gridScale;
public:
	grid(int a_rows, int a_columns, int a_scale);
	~grid();
	void setSize(int a_rows, int a_columns);
	void setGridScale(float a_scale);
	void initNodes(void);
};