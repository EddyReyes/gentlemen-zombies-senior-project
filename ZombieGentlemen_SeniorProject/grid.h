#include "dxManager.h"
#include "object.h"

class grid
{
private:
	D3DXVECTOR3 ** nodes;
	float zAxis;
	int rows, columns;
	float gridScale;
public:
	grid(int a_rows, int a_columns, float a_scale);
	~grid();
	void setSize(int a_rows, int a_columns);
	void setGridScale(float a_scale);
	void initNodes(void);
	void grid::setZAxis(float a_axis);
	D3DXVECTOR3 * getNode(int row, int column);
	int getRows(void);
	int getColumns(void);
	float getScale(void);
	float getZAxis(void);
};