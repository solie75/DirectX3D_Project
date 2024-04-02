#pragma once
#include "CRenderComponent.h"
#include "CParticleUpdateShader.h"

class CStructuredBuffer;

class CParticleSystem :
    public CRenderComponent
{
private:
    CStructuredBuffer* m_ParticleBuffer;
    CStructuredBuffer* m_ParticleSpawnCountBuffer;
    CStructuredBuffer* m_ParticleModuleDataBuffer;

    tParticleModule m_ParticleModuleData;
    Ptr<CParticleUpdateShader> m_ParticleUpdateCS;

    float m_AccumulateTime;

public:
    CParticleSystem();
    ~CParticleSystem();

    CLONE(CParticleSystem);

public:
    void SetActiveModule(PARTICLE_MODULE _ModuleType, bool _b);

    // Set Spawn Num per Sec
    void SetSpawnParticleNum(int _spawnRate) { m_ParticleModuleData.SpawnRate = _spawnRate; }

    // init Spawn Color
    void SetParticleSpawnColor(Vec3 _vInitColor) { m_ParticleModuleData.vSpawnColor = _vInitColor; }

public:
    virtual void CompRender() override;
    virtual void CompFinalTick() override;
};