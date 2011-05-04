#include "background.h"

background::background()
{
	planeMaps = NULL;
	mapNames = NULL;
	imgNames = NULL;
	numPlaneMaps = 0;
}
background::~background()
{
	if(planeMaps)
	{
		for(int i = 0; i < numPlaneMaps; i++)
		{
			if(planeMaps[i])
			{
				planeMaps[i]->~planeMap();
				delete planeMaps[i];
				planeMaps[i] = NULL;
			}
		}
	}
	delete [] planeMaps;
	planeMaps = NULL;

	mapNames->~stringArray();
	imgNames->~stringArray();
}
void background::initBackground(dxManager * dxMgr, std::string filename)
{

	stringArray temp;
	temp.loadFromTextFile(filename);

	mapNames = new stringArray();
	mapNames->loadFromTextFile(temp.getStringAt(0));

	imgNames = new stringArray();
	imgNames->loadFromTextFile(temp.getStringAt(1));


	// get the number of files in the stringArray
	numPlaneMaps = mapNames->getSize();

	if(numPlaneMaps != 0)
	{
		// create an array of pointers to XY planes of that size
		planeMaps = new planeMap * [numPlaneMaps];

		// make all plane pointers null to be safe
		for(int i = 0; i < numPlaneMaps; i++)
		{
			planeMaps[i] = NULL;
		}
		// inialize the planes with the images in the array
		for(int i = 0; i < numPlaneMaps; i++)
		{
			planeMaps[i] = new planeMap(mapNames->getStringAt(i), imgNames->getStringAt(i), dxMgr);
		}
	}
}

void background::draw()
{
	for(int i = 0; i < numPlaneMaps; i++)
	{
		if(planeMaps[i] != NULL)
		{
			planeMaps[i]->draw();
		}
	}
}