#include"RObject/RMinimalObject.h"
#include"../Core/public_singleton.h"
class RLightComponent;
class RLightManage:public PublicSingleton<RLightManage>
{
	friend struct RGeometryMap;
public:
	RLightManage();
	~RLightManage();
	void AddLight(RLightComponent* lightComponent);
	void Clear();
	vector<RLightComponent*> Lights;
};