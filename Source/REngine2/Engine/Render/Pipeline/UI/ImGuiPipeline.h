#pragma once
#include"../../../EngineMinimal.h"
struct RImGuiPipeline 
{
	RImGuiPipeline(); 

	void Init(ID3D12DescriptorHeap* heap, UINT offset);

	void Draw(GameTimer& gt);

	void Exit();

protected:
	void Tick(GameTimer& gt);
};