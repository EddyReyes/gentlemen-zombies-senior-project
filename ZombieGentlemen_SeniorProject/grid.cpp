#include "grid.h"

grid::grid(int a_rows, int a_columns, int a_scale)
{
	setSize(a_rows, a_columns);
	setGridScale(a_scale);
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
void grid::setSize(int a_rows, int a_columns)
{
	rows = a_rows;
	columns = a_columns;
}
void grid::setGridScale(float a_scale)
{
	gridScale = a_scale;
}
void grid::initNodes()
{
	nodes = new D3DXVECTOR3 * [rows];
	for(int i = 0; i < rows; i++)
	{
		nodes[i] = new D3DXVECTOR3[columns];
	}
}
