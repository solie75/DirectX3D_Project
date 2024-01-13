#pragma once

struct tVertex
{
	Vec3 vPos;
	Vec4 vColor;
	Vec2 vUV;
};

typedef tVertex Vtx;


struct TransPos
{
	float TransPosX;
	float TransPosY;
	float Pad1 = 0.f;
	float Pad2 = 0.f;
};

struct tMtrlConst
{
	int arrInt[4];
	float arrFloat[4];
	Vec2 arrV2[4];
	Vec4 arrV4[4];
	Matrix arrMat[4];
};