#ifndef _STRUCT
#define _STRUCT

// Particle
struct tParticle
{
    float4 vLocalPos;
    float4 vWorldPos; // ��ƼŬ ��ġ
    float4 vWorldScale; // ��ƼŬ ũ��
    float4 vColor; // ��ƼŬ ����
    float4 vVelocity; // ��ƼŬ ���� �ӵ�
    float4 vForce; // ��ƼŬ�� �־��� ��
    float4 vRandomForce; // ��ƼŬ�� ����Ǵ� ���� ��

    float Age; // ���� �ð�
    float PrevAge; // ���� ������ �����ð�
    float NormalizedAge; // ������ �����ð��� 0~1�� ����ȭ �� ��
    float LifeTime; // ����
    float Mass; // ����
    float ScaleFactor; // �߰� ũ�� ����
    
    int Active;
    int pad;
};


struct tParticleModule
{
	// ���� ���
    float4 vSpawnColor;
    float4 vSpawnScaleMin;
    float4 vSpawnScaleMax;
    float3 vBoxShapeScale;
    float fSphereShapeRadius;
    int SpawnShapeType; // Sphere , Box
    int SpawnRate;
    int Space; // 0 World, 1 Local    
    float MinLifeTime;
    float MaxLifeTime;
    int3 spawnpad;

	// Color Change ���
    float4 vStartColor; // �ʱ� ����
    float4 vEndColor; // ���� ����

	// Scale Change ���
    float StartScale; // �ʱ� ũ��
    float EndScale; // ���� ũ��	

    int iMaxParticleCount;
    int ipad;
    
    // Add Velocity ���
    float4 vVelocityDir;
    int AddVelocityType; // 0 : From Center, 1 : Fixed Direction	
    float OffsetAngle;
    float Speed;
    int addvpad;
    
    // Drag ���
    float StartDrag;
    float EndDrag;
    
    // NoiseForce ���
    float fNoiseTerm;
    float fNoiseForce;
        
    // Render ���
    int bRotateToMoveDirection; // 1 : �ӵ����� ���(�̵� �������� ȸ��) 0 : ��� ����
    int bScaleChangeOnVelocity; // 1 : �ӵ��� ���� ũ�� ��ȭ ���, 0 : ��� ����	using Scale changing according to Velocity.
    float vMaxSpeed; // �ִ� ũ�⿡ �����ϴ� �ӷ�
    float4 vMaxScaleChangeOnVelocity; // �ӷ¿� ���� ũ�� ��ȭ�� �ִ�ġ
    int renderpad;

    // Module Check
    int Spawn;
    int ColorChange;
    int ScaleChange;
    int AddVelocity;
    
    int Drag;
    int NoiseForce;
    int Render;
    int modulepad;
};

#endif