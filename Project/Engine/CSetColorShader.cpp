#include "pch.h"
#include "CSetColorShader.h"

CSetColorShader::CSetColorShader(UINT _iGroupPerThreadX, UINT _iGroupPerThreadY, UINT _iGroupPerThreadZ)
{
	m_iGroupPerThreadX = _iGroupPerThreadX;
	m_iGroupPerThreadY = _iGroupPerThreadY;
	m_iGroupPerThreadZ = _iGroupPerThreadZ;
}

CSetColorShader::~CSetColorShader()
{
}

void CSetColorShader::SetTargetTexture(Ptr<CTexture> _tex)
{
	m_OutTex = _tex;

	if (nullptr != m_OutTex)
	{
		Vec2 vResolution = Vec2(m_OutTex->GetWidth(), m_OutTex->GetHeight());
		m_Const.arrV2[0] = vResolution;
	}
}

void CSetColorShader::UpdateCSData()
{
	m_OutTex->UpdateTexData_CS(0, false);

	// calculate
	m_iGroupX = (m_OutTex->GetWidth() / m_iGroupPerThreadX);
	m_iGroupY = (m_OutTex->GetHeight() / m_iGroupPerThreadY);
	m_iGroupZ = 1;
}

void CSetColorShader::ClearCS()
{
	m_OutTex->ClearTex_CS(false);
}
