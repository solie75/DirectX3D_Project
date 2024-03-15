#pragma once

struct tVertex
{
	Vec3 vPos;
	Vec4 vColor;
	Vec2 vUV;
};

typedef tVertex Vtx;


//struct TransPos
//{
//	float TransPosX;
//	float TransPosY;
//	float Pad1 = 0.f;
//	float Pad2 = 0.f;
//};

struct tMtrl_CB
{
	int arrInt[4];
	float arrFloat[4];
	Vec2 arrV2[4];
	Vec4 arrV4[4];
	Matrix arrMat[4];

	// Texture setting bool
	int arrTex[(UINT)MATERIAL_TEX_PARAM::TEX_END];
};

struct tTransform_CB
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;

	Matrix matWV;
	Matrix matWVP;
};

extern tTransform_CB g_transform;

struct tAnimation_CB
{
	//Vector2 SpriteSize;
	//Vector2 Offset;
	UINT SpriteNum;
	UINT CurSpriteNum;

	int pad[2];
};

struct tDebugShapeInfo
{
	SHAPE_TYPE eShape;
	Matrix matWorld;
	Vec3 vWorldPos;
	Vec3 vWorldScale;
	Vec3 vWorldRotation;
	Vec4 vColor;
};

struct tMtrlConst
{
	int arrInt[4];
	float arrFloat[4];
	Vec2 arrV2[4];
	Vec4 arrV4[4];
	Matrix arrMat[4];

	int arrTex[(UINT)MATERIAL_TEX_PARAM::TEX_END];
};