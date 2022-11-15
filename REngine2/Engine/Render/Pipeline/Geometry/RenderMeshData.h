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

	UINT ObjectIndex;
	UINT GeometryIndex;
	XMFLOAT4X4 WorldMatrix;
	XMFLOAT4X4 TextureTransform;

	RMeshComponent* Mesh;//key
};