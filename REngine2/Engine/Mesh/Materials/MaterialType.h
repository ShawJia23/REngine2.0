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
	Max,
};