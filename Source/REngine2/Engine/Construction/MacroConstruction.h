#pragma once
#include "ActorMeshConstruction.h"

#define CREATE_RENDER_DATA(T,...)\
ActorMeshConstruction::CreateMeshRenderData<T>(inObjectParam,type,##__VA_ARGS__);

#define CREATE_RENDER_DATA_BY_COMPONENT(T,Component,...)\
ActorMeshConstruction::CreateMeshRenderDataByComponent<T>(dynamic_cast<T*>(Component),##__VA_ARGS__);

//�������
#define BUILD_OBJECT_PARAMETERS_BY_COMPONENT(InComponent,InOuter)\
CreateObjectParam inObjectParam;\
inObjectParam.Outer = InOuter;\
inObjectParam.ParentComponent = InComponent;\

//Actor����
#define BUILD_OBJECT_PARAMETERS(CoreActor)\
CreateObjectParam inObjectParam;\
inObjectParam.Outer = CoreActor;\
inObjectParam.ParentComponent = CoreActor->GetTransformationComponent();

//Objectֱ�ӹ���
#define BUILD_OBJECT_PARAMETERS_BY_NO_COMPONENT(CoreComponent)\
CreateObjectParam inObjectParam;\
inObjectParam.Outer = CoreComponent;