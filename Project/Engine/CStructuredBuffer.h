#pragma once
#include "CEntity.h"
class CStructuredBuffer :
    public CEntity
{
public:
    CStructuredBuffer();
    ~CStructuredBuffer();

    CLONE_DISABLE(CStructuredBuffer);

private:
    ComPtr<ID3D11Buffer> m_SB;
    ComPtr<ID3D11ShaderResourceView> m_SRV;
    ComPtr<ID3D11UnorderedAccessView> m_UAV;

    ComPtr<ID3D11Buffer> m_SB_CPU_Read;
    ComPtr<ID3D11Buffer> m_SB_CPU_Write;

    D3D11_BUFFER_DESC m_tDesc;

    UINT m_iStructureByteStride;
    UINT m_iNumElements;

    SB_TYPE m_SBType;
    bool m_bSysAccess;

    UINT m_iRecentRegisterNum; // 이걸 사용하는 이유가 뭐지..?

public:
    void CreateSB(UINT _iStructureByteStride, UINT _iNumElements
        , SB_TYPE _type, bool _bSysAccess, void* _pSysMem = nullptr);
    void SetSBData(void* _pSrc, UINT _iSize);
    void GetSBData(void* _pDst);

    void UpdateSBData(UINT _iRegisterNum, UINT _iPipelineStage);
    void UpdateSBData_CS(UINT _iRegisterNum, bool _IsShaderRes);

    void ClearSB();
    void ClearSB_CS(bool _isShaderRes);

    UINT GetSBSize();
};

