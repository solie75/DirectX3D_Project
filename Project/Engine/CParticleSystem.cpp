#include "pch.h"
#include "CParticleSystem.h"
#include "CResMgr.h"
#include "CStructuredBuffer.h"
#include "CTimeMgr.h"

CParticleSystem::CParticleSystem()
    : CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
    , m_ParticleBuffer(nullptr)
    , m_ParticleSpawnCountBuffer(nullptr)
    , m_ParticleModuleDataBuffer(nullptr)
    , m_ParticleModuleData{}
	, m_AccumulateTime(0.f)
{
    // module data hardcoding -> 추후  imgui 할 때 수정할 것
	m_ParticleModuleData.iMaxParticleCount = 3000;

	m_ParticleModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = true;
	m_ParticleModuleData.SpawnRate = 50;
	m_ParticleModuleData.vSpawnColor = Vec3(0.4f, 1.f, 0.4f);
	m_ParticleModuleData.vSpawnScaleMin = Vec3(15.f, 15.f, 1.f);
	m_ParticleModuleData.vSpawnScaleMax = Vec3(20.f, 20.f, 1.f);

	m_ParticleModuleData.SpawnShapeType = 0;
	m_ParticleModuleData.vBoxShapeScale = Vec3(200.f, 200.f, 200.f);
	m_ParticleModuleData.Space = 0; // 시뮬레이션 좌표계

	m_ParticleModuleData.MinLifeTime = 3.f;
	m_ParticleModuleData.MaxLifeTime = 5.f;

	m_ParticleModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::SCALE_CHANGE] = true;
	m_ParticleModuleData.StartScale = 1.5f;
	m_ParticleModuleData.EndScale = 0.2f;

	m_ParticleModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::COLOR_CHANGE] = true;
	m_ParticleModuleData.vStartColor = Vec3(0.2f, 0.3f, 1.0f);
	m_ParticleModuleData.vEndColor = Vec3(0.4f, 1.f, 0.4f);

	m_ParticleModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY] = true;
	m_ParticleModuleData.AddVelocityType = 0; // From Center
	m_ParticleModuleData.Speed = 300.f;
	m_ParticleModuleData.vVelocityDir = Vec3(0.f, 1.f, 0.f);
	m_ParticleModuleData.OffsetAngle;

	m_ParticleModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::DRAG] = true;
	m_ParticleModuleData.StartDrag = 500.f;
	m_ParticleModuleData.EndDrag = -500.f;

	m_ParticleModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE] = false;
	m_ParticleModuleData.fNoiseTerm = 1.f;
	m_ParticleModuleData.fNoiseForce = 100.f;

	m_ParticleModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::RENDER] = true;
	m_ParticleModuleData.bRotateToMoveDirection = true;
	m_ParticleModuleData.bScaleChangeOnVelocity = true;
	m_ParticleModuleData.vMaxScaleChangeOnVelocity = Vec3(15.f, 1.f, 1.f);
	m_ParticleModuleData.vMaxSpeed = 500.f;

	// Mesh, Material
	SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"PointMesh"));
	SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ParticleRenderMtrl"));

	// particle update compute shader
	m_ParticleUpdateCS = (CParticleUpdateShader*)CResMgr::GetInst()->FindRes<CComputeShader>(L"ParticleUpdateCS").Get();

	// particle buffer
	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->CreateSB(sizeof(tParticle), m_ParticleModuleData.iMaxParticleCount, SB_TYPE::READ_WRITE, false);

	// Buffer to carrying particle spawn number;
	m_ParticleSpawnCountBuffer = new CStructuredBuffer;
	m_ParticleSpawnCountBuffer->CreateSB(sizeof(tParticleSpawnCountBuffer), 1, SB_TYPE::READ_WRITE, true);
	
	// Module Activate and Data for Module Set
	m_ParticleModuleDataBuffer = new CStructuredBuffer;
	m_ParticleModuleDataBuffer->CreateSB(sizeof(tParticleModule), 1, SB_TYPE::READ_ONLY, true);
}

CParticleSystem::~CParticleSystem()
{
	if (nullptr != m_ParticleBuffer)
	{
		delete m_ParticleBuffer;
	}
	if (nullptr != m_ParticleSpawnCountBuffer)
	{
		delete m_ParticleSpawnCountBuffer;
	}
	if (nullptr != m_ParticleModuleDataBuffer)
	{
		delete m_ParticleModuleDataBuffer;
	}
}

void CParticleSystem::SetActiveModule(PARTICLE_MODULE _ModuleType, bool _b)
{
	m_ParticleModuleData.ModuleCheck[(UINT)_ModuleType] = _b;
}

void CParticleSystem::CompRender()
{
}

void CParticleSystem::CompFinalTick()
{
	// Calculate Spawn rate

	// Time of Spawn one particle
	float fTimePerCount = 1.f / (float)m_ParticleModuleData.SpawnRate;
	m_AccumulateTime += DT;

	// if Accumulate Time Over the per Spawn Time
	if (fTimePerCount < m_AccumulateTime)
	{
		float SpawnCountCurTick = m_AccumulateTime / fTimePerCount;
		m_AccumulateTime = fTimePerCount * ()
	}
}
