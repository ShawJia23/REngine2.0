#include"EngineEditorCommon.h"

int SelectedVariable = 0;
class GActorObject* SelectedObject = nullptr;
bool bOperationHandleSelect;
class RMeshComponent* SelectAxisComponent= nullptr;

class RMoveArrow* MoveArrow = nullptr;
class RScalingArrow* ScalingArrow = nullptr;
class RRotatorArrow* RotatorArrow = nullptr;