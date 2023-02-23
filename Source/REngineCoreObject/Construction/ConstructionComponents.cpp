#pragma once
#include"ConstructionComponents.h"
#include"../Component/RComponent.h"
namespace ConstructionComponent
{
	void UpdateConstructionComponents(RComponent* pComponent, RComponent* pParentComponent)
	{
		if (pParentComponent != pComponent)//����Attach�Լ�
		{
			//���õ�����
			pParentComponent->AddChildren(pComponent);

			//���ø�����˭
			pComponent->SetParentComponent(pParentComponent);
		}
	}

	void ConstructionComponents(const CreateObjectParam& pObjectParam, RMinimalObject* newObject)
	{
		if (RComponent* pComponent = dynamic_cast<RComponent*>(newObject))
		{
			if (pObjectParam.Outer)
			{
				//Outer��һ�����
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