#pragma once
#include"ConstructionComponents.h"
#include"../Component/RComponent.h"
namespace ConstructionComponent
{
	void UpdateConstructionComponents(RComponent* pComponent, RComponent* pParentComponent)
	{
		if (pParentComponent != pComponent)//不能Attach自己
		{
			//设置到子类
			pParentComponent->AddChildren(pComponent);

			//设置父类是谁
			pComponent->SetParentComponent(pParentComponent);
		}
	}

	void ConstructionComponents(const CreateObjectParam& pObjectParam, RMinimalObject* newObject)
	{
		if (RComponent* pComponent = dynamic_cast<RComponent*>(newObject))
		{
			if (pObjectParam.Outer)
			{
				//Outer是一个组件
				if (RComponent* InOuterComponent = dynamic_cast<RComponent*>(pObjectParam.Outer))
				{
					UpdateConstructionComponents(pComponent, InOuterComponent);
				}
				else if (pObjectParam.ParentComponent)
				{
					UpdateConstructionComponents(pComponent, pObjectParam.ParentComponent);
				}
			}
		}
	}
}