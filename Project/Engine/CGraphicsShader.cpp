#include "pch.h"
#include "CGraphicsShader.h"
#include "CPathMgr.h"
#include "CDevice.h"

CGraphicsShader::CGraphicsShader()
	: CShader(RES_TYPE::GRAPHICS_SHADER)
	, m_eTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	, m_RSType(RS_TYPE::CULL_BACK)
	, m_DSType(DS_TYPE::LESS)
	, m_BSType(BS_TYPE::DEFAULT)
	, m_Domain(DOMAIN_TYPE::DOMAIN_UNDEFINED)
{
}

CGraphicsShader::~CGraphicsShader()
{
}

void CGraphicsShader::CreateVertexShader(const wstring& _strFileName, const string& _strFuncName)
{
	// Set Shader file Path
	wstring strShaderFilePath = CPathMgr::GetInst()->GetContentPath();
	strShaderFilePath += _strFileName;

	// VertexShader Compile
	if (FAILED(D3DCompileFromFile(strShaderFilePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _strFuncName.c_str(), "vs_5_0", 0, 0, m_VSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)m_ErrBlob->GetBufferPointer()
			, "Vertex Shader Compile Failed!", MB_OK);
	}

	// Create VertexShader with Compiled Shader Blob
	DEVICE->CreateVertexShader(m_VSBlob->GetBufferPointer(), m_VSBlob->GetBufferSize()
		, nullptr, m_VS.GetAddressOf());

	// Set Input Layout
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[3] = {};

	LayoutDesc[0].SemanticName = "POSITION";
	LayoutDesc[0].SemanticIndex = 0;
	LayoutDesc[0].AlignedByteOffset = 0;
	LayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	LayoutDesc[0].InputSlot = 0;
	LayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[0].InstanceDataStepRate = 0;

	LayoutDesc[1].SemanticName = "COLOR";
	LayoutDesc[1].SemanticIndex = 0;
	LayoutDesc[1].AlignedByteOffset = 12;
	LayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	LayoutDesc[1].InputSlot = 0;
	LayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[1].InstanceDataStepRate = 0;

	LayoutDesc[2].SemanticName = "TEXCOORD";
	LayoutDesc[2].SemanticIndex = 0;
	LayoutDesc[2].AlignedByteOffset = 28;
	LayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	LayoutDesc[2].InputSlot = 0;
	LayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[2].InstanceDataStepRate = 0;

	HRESULT hr = DEVICE->CreateInputLayout(LayoutDesc, 3
		, m_VSBlob->GetBufferPointer(), m_VSBlob->GetBufferSize()
		, m_Layout.GetAddressOf());

	if (FAILED(hr))
	{
		assert(nullptr);
	}
}

void CGraphicsShader::CreatePixelShader(const wstring& _strFileName, const string& _strFuncName)
{
	// Set Shader file Path
	wstring strShaderFilePath = CPathMgr::GetInst()->GetContentPath();
	strShaderFilePath += _strFileName;

	// PixelShader Compile
	if (FAILED(D3DCompileFromFile(strShaderFilePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _strFuncName.c_str(), "ps_5_0", 0, 0, m_PSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)m_ErrBlob->GetBufferPointer()
			, "Pixel Shader Compile Failed!", MB_OK);
	}

	// Create PixelShader with Compiled Shader Blob
	DEVICE->CreatePixelShader(m_PSBlob->GetBufferPointer(), m_PSBlob->GetBufferSize()
		, nullptr, m_PS.GetAddressOf());
}

void CGraphicsShader::CreateGeometryShader(const wstring& _strFileName, const string& _strFuncName)
{
	// Set Shader file Path
	wstring strShaderFilePath = CPathMgr::GetInst()->GetContentPath();
	strShaderFilePath += _strFileName;

	// PixelShader Compile
	if (FAILED(D3DCompileFromFile(strShaderFilePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _strFuncName.c_str(), "gs_5_0", 0, 0, m_GSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)m_ErrBlob->GetBufferPointer()
			, "Geometry Shader Compile Failed!", MB_OK);
	}

	// Create PixelShader with Compiled Shader Blob
	DEVICE->CreateGeometryShader(m_GSBlob->GetBufferPointer(), m_GSBlob->GetBufferSize()
		, nullptr, m_GS.GetAddressOf());
}

void CGraphicsShader::SetTopology(D3D11_PRIMITIVE_TOPOLOGY _topology)
{
	m_eTopology = _topology;
}

void CGraphicsShader::UpdateShaderDate()
{
	CONTEXT->IASetInputLayout(m_Layout.Get());
	CONTEXT->IASetPrimitiveTopology(m_eTopology);

	CONTEXT->VSSetShader(m_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(m_PS.Get(), nullptr, 0);

	CONTEXT->RSSetState(CDevice::GetInst()->GetRSState(m_RSType).Get());
	CONTEXT->OMSetDepthStencilState(CDevice::GetInst()->GetDSState(m_DSType).Get(), 10);
	CONTEXT->OMSetBlendState(CDevice::GetInst()->GetBState(m_BSType).Get(), Vec4(0.f, 0.f, 0.f, 0.f), 0xffffffff);
}