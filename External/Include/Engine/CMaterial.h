#pragma once
#include "CRes.h"
#include "ptr.h"
#include "CShader.h"
#include "CTexture.h"


class CMaterial :
    public CRes
{
private:
    Ptr<CShader> m_pShader;
    tMtrl_CB m_MtrlConst;
    Ptr<CTexture> m_arrTex[TEX_END];

public:
    CMaterial(bool _bEngine = false);
    ~CMaterial();

public:
    CLONE(CMaterial);

private:
    virtual HRESULT LoadRes(const wstring& _strFilePath);

public:
    virtual HRESULT SaveRes(const wstring& _strFilePath);

public:
    void SetShader(Ptr<CShader> _shader);
    Ptr<CShader> GetShader();

    void SetMtrlScalarParam(MATERIAL_SCALAR_PARAM _param, const void* _src);
    void SetMtrlTexParam(MATERIAL_TEX_PARAM _param, const Ptr<CTexture>& _Tex);

    void GetMtrlScalarParam(MATERIAL_SCALAR_PARAM _param, void* _pData);
    Ptr<CTexture> GetTexParam(MATERIAL_TEX_PARAM _param);

    void UpdateMtrlData();
};

