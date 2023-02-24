#pragma once
#include "ActorMeshConstruction.h"

#define CREATE_RENDER_DATA(T,...)\
ActorMeshConstruction::CreateMeshRenderData<T>(inObjectParam,GetMeshManage(),type,__VA_ARGS__);

#define CREATE_RENDER_DATA_BY_COMPONENT(T,Component,...)\
ActorMeshConstruction::CreateMeshRenderDataByComponent<T>(GetMeshManage(), dynamic_cast<T*>(Component),__VA_ARGS__);

//�������
#define BUILD_OBJECT_PARAMETERS_BY_COMPONENT(InName,InComponent,InOuter)\
CreateObjectParam inObjectParam;\
inObjectParam.Outer = InOuter;\
inObjectParam.ParentComponent = InComponent;\
inObjectParam.Name = InName;

//Actor����
#define BUILD_OBJECT_PARAMETERS(Name,CoreActor)\
CreateObjectParam Param##Name;\
Param##Name.Outer = CoreActor;\
Param##Name.ParentComponent = CoreActor->GetTransformationComponent();

//Objectֱ�ӹ���
#define BUILD_OBJECT_PARAMETERS_BY_NO_COMPONENT(Name,CoreComponent)\
CreateObjectParam Param##Name;\
Param##Name.Outer = CoreComponent;