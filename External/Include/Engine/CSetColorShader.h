#pragma once
#include "CComputeShader.h"
#include "ptr.h"
#include "CTexture.h"

class CSetColorShader :
    public CComputeShader
{
public:
    CSetColorShader(UINT _iGroupPerThreadX, UINT _iGroupPerThreadY, UINT _iGroupPerThreadZ);
    ~CSetColorShader();

private:
    Ptr<CTexture> m_OutTex;

public:
    void SetTargetTexture(Ptr<CTexture> _tex);
    void SetColor(Vec3 _rgb) { m_Const.arrV4[0] = _rgb; }

public:
    virtual void UpdateCSData() override;
    virtual void ClearCS() override;
};

