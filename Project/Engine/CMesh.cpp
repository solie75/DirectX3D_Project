#include "pch.h"
#include "CMesh.h"
#include "CDevice.h"

CMesh::CMesh(bool _bEngine)
	: CRes(RES_TYPE::MESH, _bEngine)
	, m_tVBDesc{}
	, m_tIBDesc{}
	, m_IdxCount(0)
{
}

CMesh::~CMesh()
{

}

void CMesh::CreateMesh(void* _VtxSysMem, UINT _VtxCount, void* _IdxSysMem, UINT _IdxCount)
{
	m_IdxCount = _IdxCount;

	// Vertex Buffer 持失
	m_tVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	m_tVBDesc.CPUAccessFlags = 0;
	m_tVBDesc.Usage = D3D11_USAGE_DEFAULT;
	m_tVBDesc.ByteWidth = sizeof(Vtx) * _VtxCount;
	
	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = _VtxSysMem;

	HRESULT hr = DEVICE->CreateBuffer(&m_tVBDesc, &tSub, m_VB.GetAddressOf());
	if (FAILED(hr))
	{
		assert(nullptr);
	}

	// Index Buffer 持失
	m_tIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	m_tIBDesc.CPUAccessFlags = 0;
	m_tIBDesc.Usage = D3D11_USAGE_DEFAULT;
	m_tIBDesc.ByteWidth = sizeof(int) * m_IdxCount;

	tSub.pSysMem = _IdxSysMem;
	if (FAILED(DEVICE->CreateBuffer(&m_tIBDesc, &tSub, m_IB.GetAddressOf())))
	{
		assert(nullptr);
	}
}

void CMesh::UpdateMeshData()
{
	UINT iStride = sizeof(Vtx);
	UINT iOffset = 0;

	CONTEXT->IASetVertexBuffers(0, 1, m_VB.GetAddressOf(), &iStride, &iOffset);
	CONTEXT->IASetIndexBuffer(m_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void CMesh::RenderMesh()
{
	UpdateMeshData();
	CONTEXT->DrawIndexed(m_IdxCount, 0, 0);
}
