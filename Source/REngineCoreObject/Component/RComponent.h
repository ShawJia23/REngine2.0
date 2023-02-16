#pragma once
#include"../RObject/RMinimalObject.h"
class RENGINECOREOBJECT_API RComponent : public RMinimalObject
{
public:
	RComponent();

	void SetParentComponent(RComponent* InParent) { Parent = InParent; }
	void AddChildren(RComponent* InChildren);

	template<class T>
	void CallChildren(std::function<void(T*)> Func)
	{
		for (auto& Tmp : Children)
		{
			Func(dynamic_cast<T*>(Tmp));
		}
	}

public:
	FORCEINLINE std::vector<RComponent*>& GetChildrens() { return Children; }

protected:
	RComponent* Parent;
	std::vector<RComponent*> Children;
};