#pragma once
#include "CShader.h"
class CComputeShader :
    public CShader
{
public:
    CComputeShader();
    ~CComputeShader();
private:
    ComPtr<ID3D11ComputeShader> m_CS;
    ComPtr<ID3DBlob> m_CSBlob;

protected:
    // Constant data passed to the shader
    tMtrl_CB m_Const;

    // number of Group
    UINT    m_iGroupX;
    UINT    m_iGroupY;
    UINT    m_iGroupZ;

    // number of Thread per Group
    UINT    m_iGroupPerThreadX;
    UINT    m_iGroupPerThreadY;
    UINT    m_iGroupPerThreadZ;

public:
    void CreateComputeShader(const wstring& _strFileName, const string& _strFuncName);
    void ExecuteCS();

private:
    virtual void UpdateCSData() = 0;
    virtual void ClearCS() = 0;

    CLONE_DISABLE(CComputeShader);
};

