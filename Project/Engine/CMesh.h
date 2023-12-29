#pragma once

class CMesh
{
public:
    CMesh();
    ~CMesh();

private:
    ComPtr<ID3D11Buffer> m_VB;
    D3D11_BUFFER_DESC m_tVBDesc;
    UINT m_VtxCount; // ���� �� vertex buffer ����

    ComPtr<ID3D11Buffer> m_IB;
    D3D11_BUFFER_DESC m_tIBDesc;
    UINT m_IdxCount; // �� �ε��� ��

    void* m_pVtxSys;
    void* m_pIdxSys; // ���� ���� �������ΰ�?

public:
    void CreateMesh(void* _VtxSysMem, UINT _iVtxCount, void* _IdxSysMem, UINT _IdxCount);

public:
    void UpdateMeshData();
    void RenderMesh();
};

