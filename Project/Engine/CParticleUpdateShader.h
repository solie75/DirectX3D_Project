#pragma once
#include "CComputeShader.h"
#include "ptr.h"
#include "CTexture.h"

class CStructuredBuffer;

class CParticleUpdateShader :
    public CComputeShader
{
private:
    CStructuredBuffer* m_ParticleBuffer;
    CStructuredBuffer* m_ParticleCountBuffer;
    CStructuredBuffer* m_ParticleModuleData;
    Ptr<CTexture> m_NoiseTex;

public:
    CParticleUpdateShader(UINT _iGroupPerThreadX, UINT _iGroupPerThreadY, UINT _iGroupPerThreadZ);
    ~CParticleUpdateShader();

public:
    void SetParticleBuffer(CStructuredBuffer* _buffer);
    void SetParticleCountBuffer(CStructuredBuffer* _buffer);
    void SetParticleModuleData(CStructuredBuffer* _buffer);
    void SetNoiseTexture(Ptr<CTexture> _tex);

    void SetParticleObjectPos(Vec3 _vPos) { m_Const.arrV4[0] = _vPos; }

public:
    virtual void  UpdateCSData() override;
    virtual void  ClearCS() override;
};