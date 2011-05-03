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

void background::adjustPlanes(cubeMap * map, float depth)
{
	for(int i = 0; i < numPlaneMaps; i++)
	{
		if(planeMaps[i] != NULL)
		{
			////planes[i]->setParam(-10 * (i+2), map->getScale() * 10, (((i+2))  * map->getScale()/2), ((map->getWidth() * map->getScale()) +  (10 * (i+2))), map->getScale() * (10 * (i+2)));
			////planes[i]->setPosition(-10 * (i+2), map->getScale() * 10 * (i+2), (((i+2))  * map->getScale()/2));
			//planes[i]->setPosition(-1 * depth * (i+1), depth * (i+1), (i+1) * depth);
			////planes[i]->setSize(((map->getWidth() * map->getScale()) +  (10 * (i+2))), map->getScale() * (10 * (i+2)) *2);
			////planes[i]->setSize(((10 * (i+1) * 2) + map->getWidth() *map->getScale() * (i+2)), ((10 * (i+1) * 2) + map->getWidth() *map->getScale() * (i+2)));
			//planes[i]->setSize(((map->getWidth() * map->getScale() * (i+1)) + (depth * (i+1) * 2)), map->getHeight() * map->getScale() * 2 * (i+1));
			////planes[i]->setScale((i+1) * 10);
			planeMaps[i]->offsetMap(D3DXVECTOR3(-1 * planeMaps[i]->getScale(), 0.5 * planeMaps[i]->getScale() *  planeMaps[i]->getHeight(), 0));
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