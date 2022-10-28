#pragma once
#include"../../../Interface/DXDeviceInterface.h"

class RMeshComponent;

struct RRenderData :public IDirectXDeviceInterface_Struct
{
public:
	RRenderData();

	UINT IndexSize;
	UINT VertexSize;

	UINT IndexOffsetPosition;
	UINT VertexOffsetPosition;

	UINT VertexTypeSize;
	UINT IndexTypeSize;

public:
	UINT GetVertexSizeInBytes()const { return VertexSize * VertexTypeSize; }
	UINT GetIndexSizeInBytes()const { return IndexSize * IndexTypeSize; }
public:
	DXGI_FORMAT IndexFormat;

	XMFLOAT4X4 WorldMatrix;

	RMeshComponent* Mesh;//key
};