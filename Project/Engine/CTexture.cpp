#include "pch.h"
#include "CTexture.h"
#include "CDevice.h"

CTexture::CTexture(bool _bEngine)
    : CRes(RES_TYPE::TEXTURE, _bEngine)
	, m_pImage(new ScratchImage)
	, m_Tex2DDesc{}
{
}

CTexture::~CTexture()
{
}

HRESULT CTexture::LoadRes(const wstring& _strFilePath)
{
    wchar_t szExt[50] = L"";
    _wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 50);
    wstring strExt = szExt;

    HRESULT hr = S_OK;

	if (L".dds" == strExt || L".DDS" == strExt)
	{
		// dds, DDS
		hr = LoadFromDDSFile(_strFilePath.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, *m_pImage);
	}

	else if (L".tga" == strExt || L".TGA" == strExt)
	{
		// tga, TGA
		hr = LoadFromTGAFile(_strFilePath.c_str(), nullptr, *m_pImage);
	}

	else
	{
		// png, jpg, jpeg, bmp
		hr = LoadFromWICFile(_strFilePath.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, *m_pImage);
	}

	if (FAILED(hr))
	{
		//MessageBox(nullptr, L"리소스 로딩 실패", L"텍스쳐 로딩 실패", MB_OK);
		return E_FAIL;
	}

	hr = CreateShaderResourceView(DEVICE
		, m_pImage->GetImages()
		, m_pImage->GetImageCount()
		, m_pImage->GetMetadata()
		, m_SRV.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"ShaderResourceView 생성 실패", L"텍스쳐 로딩 실패", MB_OK);
		return E_FAIL;
	}

	m_SRV->GetResource((ID3D11Resource**)m_Tex2D.GetAddressOf());
	m_Tex2D->GetDesc(&m_Tex2DDesc);

    return S_OK;
}

HRESULT CTexture::SaveRes(const wstring& _strFilePath)
{
    return S_OK;
}

void CTexture::UpdateTexData(int _iRegisterNum)
{
	CONTEXT->PSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
}

void CTexture::ClearTexRegister(int _iRegisterNum)
{
	ID3D11ShaderResourceView* pSRV = nullptr;

	/*CONTEXT->VSSetShaderResources(_iRegisterNum, 1, &pSRV);
	CONTEXT->HSSetShaderResources(_iRegisterNum, 1, &pSRV);
	CONTEXT->DSSetShaderResources(_iRegisterNum, 1, &pSRV);
	CONTEXT->GSSetShaderResources(_iRegisterNum, 1, &pSRV);*/
	CONTEXT->PSSetShaderResources(_iRegisterNum, 1, &pSRV);
}

//Vec2 CTexture::GetScratchImageSize()
//{
//	Vec2 tempV2;
//	tempV2.x = m_Image.GetMetadata().width;
//	tempV2.y = m_Image.GetMetadata().height;
//	return tempV2;
//}

//void CTexture::ClearAllTexRegister()
//{
//	ID3D11ShaderResourceView* pSRV = nullptr;
//	CONTEXT->VSSetShaderResources(m_iRecentNum, 1, &pSRV);
//	CONTEXT->HSSetShaderResources(m_iRecentNum, 1, &pSRV);
//	CONTEXT->DSSetShaderResources(m_iRecentNum, 1, &pSRV);
//	CONTEXT->GSSetShaderResources(m_iRecentNum, 1, &pSRV);
//	CONTEXT->PSSetShaderResources(m_iRecentNum, 1, &pSRV);
//}
