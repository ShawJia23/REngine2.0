#pragma once
enum EMaterialType
{
	Lambert = 0,
	HalfLambert = 1,
	Phong = 2,
	BlinnPhong = 3,
	WrapLight = 4,
	Minnaert = 5,
	Banded = 6,
	GradualBanded = 7,
	FinalBanded = 8,
	Back = 9,
	AnisotropKajiya=10,
	OrenNayar=11,
	PBR =12,
	BaseColor=13,
	WorldNormal = 14,
	Normal = 15,
	MaterialMax,
};

//‰÷»æÕÿ∆À
enum EMaterialDisplayStatue
{
	RTOPOLOGY_UNDEFINED = 0,
	RTOPOLOGY_POINTLIST = 1,
	RTOPOLOGY_LINELIST = 2,
	RTOPOLOGY_LINESTRIP = 3,
	RTOPOLOGY_TRIANGLELIST = 4,
};