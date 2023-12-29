#include "pch.h"
#include "CShader.h"
#include "CPathMgr.h"
#include "CDevice.h"

CShader::CShader()
	: m_eTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
}

CShader::~CShader()
{
}

void CShader::ShaderInit()
{
	CreateVertexShader(L"Shader\\std2D.fx", "VS_Std2D");
	CreatePixelShader(L"Shader\\std2D.fx", "PS_Std2D");
	this->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void CShader::CreateVertexShader(const wstring& _strFileName, const string& _strFuncName)
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
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[2] = {};
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

	HRESULT hr = DEVICE->CreateInputLayout(LayoutDesc, 2
		, m_VSBlob->GetBufferPointer(), m_VSBlob->GetBufferSize()
		, m_Layout.GetAddressOf());

	if (FAILED(hr))
	{
		assert(nullptr);
	}
}

void CShader::CreatePixelShader(const wstring& _strFileName, const string& _strFuncName)
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

void CShader::SetTopology(D3D11_PRIMITIVE_TOPOLOGY _topology)
{
	m_eTopology = _topology;
}

void CShader::UpdateShaderDate()
{
	CONTEXT->IASetInputLayout(m_Layout.Get());
	CONTEXT->IASetPrimitiveTopology(m_eTopology);

	CONTEXT->VSSetShader(m_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(m_PS.Get(), nullptr, 0);
}
