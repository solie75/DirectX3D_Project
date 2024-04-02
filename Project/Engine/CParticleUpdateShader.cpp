#include "pch.h"
#include "CParticleUpdateShader.h"
#include "CStructuredBuffer.h"

CParticleUpdateShader::CParticleUpdateShader(UINT _iGroupPerThreadX, UINT _iGroupPerThreadY, UINT _iGroupPerThreadZ)
	: m_ParticleBuffer(nullptr)
	, m_ParticleCountBuffer(nullptr)
	, m_ParticleModuleData(nullptr)
{
	m_iGroupPerThreadX = _iGroupPerThreadX;
	m_iGroupPerThreadY = _iGroupPerThreadY;
	m_iGroupPerThreadZ = _iGroupPerThreadZ;
}

CParticleUpdateShader::~CParticleUpdateShader()
{
}

void CParticleUpdateShader::SetParticleBuffer(CStructuredBuffer* _buffer)
{
	m_ParticleBuffer = _buffer;
	m_Const.arrInt[0] = m_ParticleBuffer->GetElementNum();
}

void CParticleUpdateShader::SetParticleCountBuffer(CStructuredBuffer* _buffer)
{
	m_ParticleCountBuffer = _buffer;
}

void CParticleUpdateShader::SetParticleModuleData(CStructuredBuffer* _buffer)
{
	m_ParticleModuleData = _buffer;
}

void CParticleUpdateShader::SetNoiseTexture(Ptr<CTexture> _tex)
{
	m_NoiseTex = _tex;
	m_Const.arrV2[0] = Vec2(m_NoiseTex->GetWidth(), m_NoiseTex->GetHeight());
}

void CParticleUpdateShader::UpdateCSData()
{
	m_ParticleBuffer->UpdateSBData_CS(0, false);
	m_ParticleCountBuffer->UpdateSBData_CS(1, false);
	m_ParticleModuleData->UpdateSBData_CS(20, true);
	m_NoiseTex->UpdateTexData_CS(21, true);

	m_iGroupX = (m_ParticleBuffer->GetElementNum() / m_iGroupPerThreadX) + 1;
}

void CParticleUpdateShader::ClearCS()
{
	m_ParticleBuffer->ClearSB_CS(false);
	m_ParticleCountBuffer->ClearSB_CS(false);
	m_ParticleModuleData->ClearSB_CS(true);
	m_NoiseTex->ClearTex_CS(true);
}
