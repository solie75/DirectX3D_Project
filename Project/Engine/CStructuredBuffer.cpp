#include "pch.h"
#include "CStructuredBuffer.h"
#include "CDevice.h"

CStructuredBuffer::CStructuredBuffer()
	: m_iStructureByteStride(0)
	, m_iNumElements(0)
{
}

CStructuredBuffer::~CStructuredBuffer()
{
}

void CStructuredBuffer::CreateSB(UINT _iStructureByteStride, UINT _iNumElements
	, SB_TYPE _type, bool _bSysAccess, void* _pSysMem)
{
	m_SB = nullptr;
	m_SRV = nullptr;
	m_UAV = nullptr;

	m_SB_CPU_Read = nullptr;
	m_SB_CPU_Write = nullptr;

	m_SBType = _type;
	m_bSysAccess = _bSysAccess;

	m_iStructureByteStride = _iStructureByteStride;
	m_iNumElements = _iNumElements;

	UINT tempBufferSize = m_iStructureByteStride * m_iNumElements;

	assert(!(tempBufferSize & 16)); // 16바이트 단위 메모리 정렬

	// Create Structured Buffer
	m_tDesc.ByteWidth = tempBufferSize;
	m_tDesc.StructureByteStride = m_iStructureByteStride;
	
	if (SB_TYPE::READ_ONLY == m_SBType)
	{
		m_tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE; // flag for binding to Texture Register
	}
	else if (SB_TYPE::READ_WRITE == m_SBType)
	{
		m_tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	}

	// Specifies that the buffer being created is a structured buffer.
	m_tDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

	m_tDesc.Usage = D3D11_USAGE_DEFAULT;
	m_tDesc.CPUAccessFlags = 0;

	if (nullptr == _pSysMem)
	{
		if (FAILED(DEVICE->CreateBuffer(&m_tDesc, nullptr, m_SB.GetAddressOf())))
		{
			assert(nullptr);
		}
	}
	else // 기본적으로 _pSysMem 을 nullptr 로 할 거면서 else 의 경우는 어떤 경우인가?
	{
		D3D11_SUBRESOURCE_DATA tSubData = {};
		tSubData.pSysMem = _pSysMem;

		HRESULT hr = DEVICE->CreateBuffer(&m_tDesc, &tSubData, m_SB.GetAddressOf());
		if (hr)
		{
			assert(nullptr);
		}
	}

	// Creat ShaderResourceView
	D3D11_SHADER_RESOURCE_VIEW_DESC m_SRVDesc = {};
	m_SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	m_SRVDesc.BufferEx.NumElements = m_iNumElements;

	if (FAILED(DEVICE->CreateShaderResourceView(m_SB.Get(), &m_SRVDesc, m_SRV.GetAddressOf())))
	{
		assert(nullptr);
	}

	
	if (SB_TYPE::READ_WRITE == m_SBType)
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC m_UAVDesc = {};
		m_UAVDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		m_UAVDesc.Buffer.NumElements = m_iNumElements;

		if (FAILED(DEVICE->CreateUnorderedAccessView(m_SB.Get(), &m_UAVDesc, m_UAV.GetAddressOf())))
		{
			assert(nullptr);
		}
	}

	// Create CPU Access Assistant Buffer
	if (m_bSysAccess)
	{
		m_tDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;

		// Cpu read gpu's Resource
		m_tDesc.Usage = D3D11_USAGE_DEFAULT;
		m_tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

		if (FAILED(DEVICE->CreateBuffer(&m_tDesc, nullptr, m_SB_CPU_Read.GetAddressOf())))
		{
			assert(nullptr);
		}

		// Cpu write data in gpu's Resource
		m_tDesc.Usage = D3D11_USAGE_DYNAMIC;
		m_tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		if (FAILED(DEVICE->CreateBuffer(&m_tDesc, nullptr, m_SB_CPU_Write.GetAddressOf())))
		{
			assert(nullptr);
		}
	}
}

void CStructuredBuffer::SetSBData(void* _pSrc, UINT _iSize)
{
	if (nullptr == _pSrc)
	{
		return;
	}

	UINT tempSize = _iSize;
	if (0 == tempSize)
	{
		tempSize = GetSBSize();
	}

	// Set Data(_pSrc) to Cpu write buffer(m_SB_CPU_write)
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(m_SB_CPU_Write.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, _pSrc, tempSize);
	CONTEXT->Unmap(m_SB_CPU_Write.Get(), 0);

	// Copy Cpu write buffer (m_SB_CPU_Write) to Main buffer (m_SB)
	CONTEXT->CopyResource(m_SB.Get(), m_SB_CPU_Write.Get());
}

void CStructuredBuffer::GetSBData(void* _pDst)
{
	// Copy Main buffer to Cpu read buffer
	CONTEXT->CopyResource(m_SB_CPU_Read.Get(), m_SB.Get());

	// Set Data(m_SB_CPU_read) to _pDst
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(m_SB_CPU_Read.Get(), 0, D3D11_MAP::D3D11_MAP_READ, 0, &tSub);
	memcpy(_pDst, tSub.pData, GetSBSize());
	CONTEXT->Unmap(m_SB_CPU_Read.Get(), 0);
}

void CStructuredBuffer::UpdateSBData(UINT _iRegisterNum, UINT _iPipelineStage)
{
	m_iRecentRegisterNum = _iRegisterNum;

	if (PIPELINE_STAGE::PS_VERTEX & _iPipelineStage)
	{
		CONTEXT->VSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}

	if (PIPELINE_STAGE::PS_HULL & _iPipelineStage)
	{
		CONTEXT->HSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}

	if (PIPELINE_STAGE::PS_DOMAIN & _iPipelineStage)
	{
		CONTEXT->DSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}

	if (PIPELINE_STAGE::PS_GEOMETRY & _iPipelineStage)
	{
		CONTEXT->GSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}

	if (PIPELINE_STAGE::PS_PIXEL & _iPipelineStage)
	{
		CONTEXT->PSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}
}

void CStructuredBuffer::UpdateSBData_CS(UINT _iRegisterNum, bool _isShaderRes)
{
	m_iRecentRegisterNum = _iRegisterNum;

	if(_isShaderRes)
	{
		CONTEXT->CSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}
	else
	{
		UINT i = -1;
		CONTEXT->CSSetUnorderedAccessViews(_iRegisterNum, 1, m_UAV.GetAddressOf(), &i);
	}
}

void CStructuredBuffer::ClearSB()
{
	ID3D11ShaderResourceView* pSRV = nullptr;
	CONTEXT->VSSetShaderResources(m_iRecentRegisterNum, 1, &pSRV);
	CONTEXT->HSSetShaderResources(m_iRecentRegisterNum, 1, &pSRV);
	CONTEXT->DSSetShaderResources(m_iRecentRegisterNum, 1, &pSRV);
	CONTEXT->GSSetShaderResources(m_iRecentRegisterNum, 1, &pSRV);
	CONTEXT->PSSetShaderResources(m_iRecentRegisterNum, 1, &pSRV);
	CONTEXT->CSSetShaderResources(m_iRecentRegisterNum, 1, &pSRV);
}

void CStructuredBuffer::ClearSB_CS(bool _isShaderRes)
{
	if (_isShaderRes)
	{
		ID3D11ShaderResourceView* pSRV = nullptr;
		CONTEXT->CSSetShaderResources(m_iRecentRegisterNum, 1, &pSRV);
	}
	else
	{
		ID3D11UnorderedAccessView* pUAV = nullptr;
		UINT i = -1;
		CONTEXT->CSSetUnorderedAccessViews(m_iRecentRegisterNum, 1, &pUAV, &i);
	}
}

UINT CStructuredBuffer::GetSBSize()
{
	return m_iStructureByteStride * m_iNumElements;
}
