#pragma once
#include "ActorMeshConstruction.h"

#define CREATE_RENDER_DATA(T,...)\
ActorMeshConstruction::CreateMeshRenderData<T>(GetMeshManage(),type,__VA_ARGS__);

