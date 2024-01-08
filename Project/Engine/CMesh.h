#pragma once
#include "CRes.h"

class CMesh
    : public CRes
{
public:
    CMesh(bool _bEngine);
    ~CMesh();

private:
    ComPtr<ID3D11Buffer> m_VB;
    D3D11_BUFFER_DESC m_tVBDesc;
    //UINT m_VtxCount; // ��� ���� �ʳ�?

    ComPtr<ID3D11Buffer> m_IB;
    D3D11_BUFFER_DESC m_tIBDesc;
    UINT m_IdxCount; // �ε��� ������ draw �Լ����� ���ȴٰ� ������ ���� ������ ��� ����..?
   
public:
    void CreateMesh(void* _VtxSysMem, UINT _iVtxCount, void* _IdxSysMem, UINT _IdxCount);

public:
    void UpdateMeshData();
    void RenderMesh();

private:
    virtual HRESULT LoadRes(const wstring& _strFilePath) { return S_OK; }

public:
    virtual HRESULT SaveRes(const wstring& _strFilePath) { return S_OK; }
};

