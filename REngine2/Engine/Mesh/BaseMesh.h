#pragma once
#include "Core/Mesh.h"

class BoxMesh :public BMesh
{
	typedef BMesh Super;
public:
	virtual void Init();

	virtual void Draw(float DeltaTime);

	void CreateMesh(float height,float width,float depth);
};

class ConeMesh :public BMesh
{
	typedef BMesh Super;
public:
	virtual void Init();

	virtual void Draw(float DeltaTime);

	void CreateMesh(float radius, float height, uint32_t axialSub, uint32_t heightSub);
};

class CylinderMesh :public BMesh
{
	typedef BMesh Super;
public:
	virtual void Init();

	virtual void Draw(float DeltaTime);

	void CreateMesh(float topRadius, float bottomRadius, float height, uint32_t axialSub, uint32_t heightSub);
};

class PlaneMesh :public BMesh
{
	typedef BMesh Super;
public:
	virtual void Init();

	virtual void Draw(float DeltaTime);

	void CreateMesh(float height, float width, uint32_t heightSub, uint32_t widthSub);
};

class SphereMesh :public BMesh
{
	typedef BMesh Super;
public:
	virtual void Init();

	virtual void Draw(float DeltaTime);

	void CreateMesh(float radius, uint32_t axialSub, uint32_t heightSub);
};

class CustomMesh :public BMesh
{
	typedef BMesh Super;
public:
	virtual void Init();

	virtual void Draw(float DeltaTime);

	void CreateMesh(string path);
};