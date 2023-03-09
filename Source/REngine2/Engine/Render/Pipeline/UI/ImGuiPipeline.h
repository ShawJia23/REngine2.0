#pragma once
#include"../../../Interface/DXDeviceInterface.h"

struct RImGuiPipeline :public IDirectXDeviceInterface_Struct 
{
	RImGuiPipeline(); 

	void Init(ID3D12DescriptorHeap* heap, UINT offset);

	void Draw(GameTimer& gt);

	void Exit();

protected:
	void Tick(GameTimer& gt);
};