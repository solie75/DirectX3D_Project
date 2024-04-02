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

struct tParticle
{
	Vec4	vLocalPos;		// 오브젝트로부터 떨어진 거리
	Vec4	vWorldPos;		// 파티클 최종 월드위치
	Vec4	vWorldScale;	// 파티클 크기	
	Vec4	vColor;			// 파티클 색상
	Vec4	vVelocity;		// 파티클 현재 속도
	Vec4	vForce;			// 파티클에 주어진 힘
	Vec4	vRandomForce;	// 파티클에 적용되는 랜덤방향 힘

	float   Age;			// 생존 시간
	float   PrevAge;		// 이전 프레임 생존 시간
	float   NormalizedAge;	// 수명대비 생존시간을 0~1로 정규화 한 값
	float	LifeTime;		// 수명
	float	Mass;			// 질량
	float   ScaleFactor;	// 추가 크기 배율

	int     Active;			// 파티클 활성화 여부
	int     pad;
};

struct tParticleSpawnCountBuffer
{
	int		SpawnCount;			// 스폰 시킬 파티클 개수
	int		padding[3];
};

struct tParticleModule
{
	// 스폰 모듈
	Vec4    vSpawnColor;
	Vec4	vSpawnScaleMin;
	Vec4	vSpawnScaleMax;
	Vec3	vBoxShapeScale;
	float	fSphereShapeRadius;
	int		SpawnShapeType;		// 0 : BOX, 1 : Sphere
	int		SpawnRate;			// 초당 생성 개수
	int		Space;				// 파티클 업데이트 좌표계 ( 0 : World,  1 : Local)
	float   MinLifeTime;		// 최소 수명
	float   MaxLifeTime;		// 최대 수명
	int     spawnpad[3];

	// Color Change 모듈
	Vec4	vStartColor;		// 초기 색상
	Vec4	vEndColor;			// 최종 색상

	// Scale Change 모듈
	float	StartScale;			// 초기 배율
	float	EndScale;			// 최종 배율	

	// 버퍼 최대크기
	int		iMaxParticleCount;
	int		ipad;

	// Add Velocity 모듈
	Vec4	vVelocityDir;
	int     AddVelocityType;	// 0 : From Center, 1: To Center, 2 : Fixed Direction	
	float	OffsetAngle;
	float	Speed;
	int     addvpad;

	// Drag 모듈 - 속도 제한
	float	StartDrag;
	float	EndDrag;

	// NoiseForce 모듈 - 랜덤 힘 적용	
	float	fNoiseTerm;		// 랜덤 힘 변경 간격
	float	fNoiseForce;	// 랜덤 힘 크기

	// Render 모듈
	int		bRotateToMoveDirection;	// 1 : 속도정렬 사용(이동 방향으로 회전) 0 : 사용 안함
	int		bScaleChangeOnVelocity;		// 1 : 속도에 따른 크기 변화 사용, 0 : 사용 안함	
	float   vMaxSpeed;			// 최대 크기에 도달하는 속력
	Vec4	vMaxScaleChangeOnVelocity;	// 속력에 따른 크기 변화량 최대치
	int		renderpad;

	// Module Check
	int		ModuleCheck[(UINT)PARTICLE_MODULE::END];
};

struct tGlobal
{
	Vec2 Resolution;
	float DeltaTime;
	float AccumulateTime;
};

extern tGlobal GlobalData;