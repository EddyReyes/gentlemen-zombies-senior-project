#include "grid.h"

// defualt constructor
grid::grid(){}

grid::grid(int a_rows, int a_columns, float a_scale)
{
	setSize(a_rows, a_columns);
	setGridScale(a_scale);
	zAxis = 0.0f;
	initNodes();
}
grid::~grid()
{
	for(int i = 0; i < rows; i++)
	{
		delete [] nodes[i];
	}
	delete [] nodes;
}
void grid::initNodes()
{
	nodes = new D3DXVECTOR3 * [rows];
	for(int y = 0; y < rows; y++)
	{
		nodes[y] = new D3DXVECTOR3[columns];
		//initialize node data
		for(int x = 0; x < columns; x++)
		{
			nodes[y][x] = D3DXVECTOR3(x * gridScale, y * gridScale, zAxis);
		}
	}
}
// mutators
void grid::setSize(int a_rows, int a_columns)
{
	rows = a_rows;
	columns = a_columns;
}
void grid::setGridScale(float a_scale)
{
	gridScale = a_scale;
}
void grid::setZAxis(float a_axis){zAxis = a_axis;}

//accesors
D3DXVECTOR3 * grid::getNode(int row, int column){return &nodes[row][column];}
int grid::getRows(void){return rows;}
int grid::getColumns(void){return columns;}
float grid::getScale(void){return gridScale;}
float grid::getZAxis(void){return zAxis;}
