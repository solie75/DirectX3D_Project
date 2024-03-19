#pragma once
#include "CEntity.h"
class CConstBuffer :
    public CEntity
{
public:
    CConstBuffer(UINT _iRegisterNum);
    ~CConstBuffer();

private:
    ComPtr<ID3D11Buffer> m_CB;
    D3D11_BUFFER_DESC m_CBDesc;
    const UINT m_iRegisterNum;

    UINT m_iElementSize;
    UINT m_iElementCount;

public:
    void CreateCB(UINT _iElementSize, UINT _iElementCount);
    void SetCBData(void* _pSrc, UINT _iSize = 0);
    void UpdateCBData();
    void UpdateCBData_CS();
   
    CLONE_DISABLE(CConstBuffer);
};

