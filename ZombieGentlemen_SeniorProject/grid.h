#include "dxManager.h"
#include "object.h"

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