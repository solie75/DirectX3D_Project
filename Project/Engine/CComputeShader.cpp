#include "pch.h"
#include "CComputeShader.h"
#include "CPathMgr.h"
#include "CDevice.h"

CComputeShader::CComputeShader()
	: CShader(RES_TYPE::COMPUTE_SHADER)
	, m_iGroupX(1)
	, m_iGroupY(1)
	, m_iGroupZ(1)
	, m_iGroupPerThreadX(1)
	, m_iGroupPerThreadY(1)
	, m_iGroupPerThreadZ(1)
{
}

CComputeShader::~CComputeShader()
{
}

void CComputeShader::CreateComputeShader(const wstring& _strFileName, const string& _strFuncName)
{
	// Set Shader file Path
	wstring strShaderFilePath = CPathMgr::GetInst()->GetContentPath();
	strShaderFilePath += _strFileName;

	// Compute Shader Compile
	if (FAILED(D3DCompileFromFile(strShaderFilePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _strFuncName.c_str(), "cs_5_0", 0, 0, m_CSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)m_ErrBlob->GetBufferPointer()
			, "Compute Shader Compile Failed!", MB_OK);
	}

	// Create Compute Shader with Compiled Shader Blob
	DEVICE->CreateComputeShader(m_CSBlob->GetBufferPointer(), m_CSBlob->GetBufferSize()
		, nullptr, m_CS.GetAddressOf());
}

void CComputeShader::ExecuteCS()
{
	this->UpdateCSData();

	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL);
	pCB->SetCBData(&m_Const);
	pCB->UpdateCBData_CS();

	CONTEXT->CSSetShader(m_CS.Get(), nullptr, 0);
	CONTEXT->Dispatch(m_iGroupX, m_iGroupY, m_iGroupZ);

	ComPtr<ID3D11UnorderedAccessView> tempUAV;
	CONTEXT->CSGetUnorderedAccessViews(0, 1, tempUAV.GetAddressOf());
	ComPtr<ID3D11ShaderResourceView> tempSRV;
	CONTEXT->CSGetShaderResources(0, 1, tempSRV.GetAddressOf());

	this->ClearCS();
}
