#include"RMinimalObject.h"

vector<RMinimalObject*>GRObjects;

RMinimalObject::RMinimalObject() 
{
	bTick = true;
	GRObjects.push_back(this);
}
RMinimalObject::~RMinimalObject() 
{
	for (vector<RMinimalObject*>::const_iterator Iter = GRObjects.begin();
		Iter != GRObjects.end();
		++Iter)
	{
		if (*Iter == this)
		{
			GRObjects.erase(Iter);
			break;
		}
	}
}