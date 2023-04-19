#include"RObject/RMinimalObject.h"
#include"../Core/public_singleton.h"
class RLightComponent;
class RLightManage:public PublicSingleton<RLightManage>
{
	friend struct RGeometryMap;
public:
	void AddLight(RLightComponent* lightComponent);
	vector<RLightComponent*> Lights;
};