#include"RObject/RMinimalObject.h"

class RLightComponent;
class RLightManage :public RMinimalObject 
{
	friend struct RGeometryMap;
public:
	void AddLight(RLightComponent* lightComponent);
	vector<RLightComponent*> Lights;
};