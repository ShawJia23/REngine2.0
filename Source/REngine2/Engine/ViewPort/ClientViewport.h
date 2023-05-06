
#pragma once
#include "../Engine.h"
#include "Viewport.h"
#include"../Actor/ActorObject.h"
#include"ViewportData.h"

class ClientViewport :public GActorObject, public RViewport
{
	typedef RViewport SuperV;
	typedef GActorObject SuperA;

public:
	ClientViewport();

	//…Ë÷√ ”◊∂
	void SetFrustum(float InYFOV, float InZNear, float InZFar);
	void SetFrustum(float InYFOV, float InAspect, float InZNear, float InZFar);
	void FaceTarget(const fvector_3d& InPosition, const fvector_3d& InTargetPosition, const fvector_3d& InUP = fvector_3d(0.f, 1.f, 0.f));

	virtual void Tick(GameTimer& gt);
	virtual void BuildViewMatrix();
	virtual void OnResetSize(int InWidth, int InHeight);

	void BuildOrthographicOffCenterLHMatrix(float InRadius, const fvector_3d& InTargetPosition);

public:
	FORCEINLINE float GetFOV() const { return ViewportData.YFOV; }
	FORCEINLINE float GetAspect() const { return  ViewportData.Aspect; }
	FORCEINLINE float GetNear() const { return  ViewportData.ZNear; }
	FORCEINLINE float GetFar() const { return  ViewportData.ZFar; }
	FORCEINLINE int GetWidth() const { return ViewportData.Width; }
	FORCEINLINE int GetHeight() const { return ViewportData.Height; }
	FORCEINLINE bool GetDirty() const { return bDirty; }

	void SetDirty(bool bNewDirty) { bDirty = bNewDirty; }

	BoundingFrustum GetBoundingFrustum() {return m_Frustum;}
private:
	RViewportData ViewportData;

	BoundingFrustum m_Frustum;

	bool bDirty;
};