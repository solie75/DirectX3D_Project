#pragma once

class CMesh
{
public:
    CMesh();
    ~CMesh();

private:
    ComPtr<ID3D11Buffer> m_VB;
    D3D11_BUFFER_DESC m_tVBDesc;
    UINT m_VtxCount; // 사용된 총 vertex buffer 개수

    ComPtr<ID3D11Buffer> m_IB;
    D3D11_BUFFER_DESC m_tIBDesc;
    UINT m_IdxCount; // 총 인덱스 수

    void* m_pVtxSys;
    void* m_pIdxSys; // 뭐에 대한 포인터인가?

public:
    void CreateMesh(void* _VtxSysMem, UINT _iVtxCount, void* _IdxSysMem, UINT _IdxCount);

public:
    void UpdateMeshData();
    void RenderMesh();
};

