#include "pch.h"
#include "CConstBuffer.h"

#include "CDevice.h"

CConstBuffer::CConstBuffer(UINT _iRegisterNum)
	: m_iRegisterNum(_iRegisterNum)
	, m_CBDesc{}
	, m_iElementCount(0)
	, m_iElementSize(0)
{
}

CConstBuffer::~CConstBuffer()
{
}

void CConstBuffer::CreateCB(UINT _iElementSize, UINT _iElementCount)
{
	m_iElementCount = _iElementCount;
	m_iElementSize = _iElementSize;

	UINT iBufferSize = m_iElementSize * _iElementCount;

	// Memory alignment in 16-byte units
	assert(!(iBufferSize % 16));

	// Create Constant Buffer
	m_CBDesc.ByteWidth = iBufferSize;
	m_CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	m_CBDesc.Usage = D3D11_USAGE_DYNAMIC;
	m_CBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	if (FAILED(DEVICE->CreateBuffer(&m_CBDesc, nullptr, m_CB.GetAddressOf())))
	{
		assert(nullptr);
	}
}

void CConstBuffer::SetCBData(void* _pSrc, UINT _iSize)
{
	UINT tempSize = _iSize;
	if (0 == tempSize)
	{
		tempSize = m_iElementCount * m_iElementSize;
	}

	assert(!(tempSize > m_iElementSize * m_iElementCount));

	D3D11_MAPPED_SUBRESOURCE tSubRes = {};
	if (!FAILED(CONTEXT->Map(m_CB.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tSubRes)))
	{
		memcpy(tSubRes.pData, _pSrc, tempSize);
		CONTEXT->Unmap(m_CB.Get(), 0);
	}
}

void CConstBuffer::UpdateCBData()
{
	CONTEXT->VSSetConstantBuffers(m_iRegisterNum, 1, m_CB.GetAddressOf());
	//CONTEXT->HSSetConstantBuffers(m_iRegisterNum, 1, m_CB.GetAddressOf());
	//CONTEXT->DSSetConstantBuffers(m_iRegisterNum, 1, m_CB.GetAddressOf());
	CONTEXT->GSSetConstantBuffers(m_iRegisterNum, 1, m_CB.GetAddressOf());
	CONTEXT->PSSetConstantBuffers(m_iRegisterNum, 1, m_CB.GetAddressOf());
}

void CConstBuffer::UpdateCBData_CS()
{
	CONTEXT->CSSetConstantBuffers(m_iRegisterNum, 1, m_CB.GetAddressOf());
}
