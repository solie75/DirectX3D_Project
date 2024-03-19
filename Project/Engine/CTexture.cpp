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
	m_iRecentNum = _iRegisterNum;
	CONTEXT->PSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
}

void CTexture::UpdateTexData_CS(int _iRegisterNum, bool _bShaderRes)
{
	m_iRecentNum = _iRegisterNum;

	if (_bShaderRes)
	{
		CONTEXT->CSSetShaderResources(m_iRecentNum, 1, m_SRV.GetAddressOf());
	}
	else
	{
		UINT i = -1;
		CONTEXT->CSSetUnorderedAccessViews(m_iRecentNum, 1, m_UAV.GetAddressOf(), &i);
	}
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

void CTexture::ClearTex_CS(bool _bShaderRes)
{
	if (_bShaderRes)
	{
		ID3D11ShaderResourceView* pSRV = nullptr;
		CONTEXT->CSSetShaderResources(m_iRecentNum, 1, &pSRV);
	}
	else
	{
		ID3D11UnorderedAccessView* pUAV = nullptr;
		UINT i = -1;
		CONTEXT->CSSetUnorderedAccessViews(m_iRecentNum, 1, &pUAV, &i);
	}
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


void CTexture::CreateSRV()
{
	CreateShaderResourceView(
		DEVICE,
		m_pImage->GetImages(),
		m_pImage->GetImageCount(),
		m_pImage->GetMetadata(),
		m_SRV.GetAddressOf()
	);

	m_SRV->GetResource((ID3D11Resource**)m_Tex2D.GetAddressOf());
}


HRESULT CTexture::SetTexture2D(UINT _width, UINT _height, DXGI_FORMAT _pixelFormat
	, UINT _bindFlags, D3D11_USAGE _usage)
{
	m_Tex2DDesc.Format = _pixelFormat;
	m_Tex2DDesc.Width = _width;
	m_Tex2DDesc.Height = _height;
	m_Tex2DDesc.ArraySize = 1;
	m_Tex2DDesc.BindFlags = _bindFlags;
	m_Tex2DDesc.Usage = _usage;

	if (D3D11_USAGE::D3D11_USAGE_DYNAMIC == _usage)
	{
		m_Tex2DDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else if (D3D11_USAGE::D3D11_USAGE_STAGING == _usage)
	{
		m_Tex2DDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	}
	
	m_Tex2DDesc.MipLevels = 1; // Create Origin Only
	m_Tex2DDesc.SampleDesc.Count = 1;
	m_Tex2DDesc.SampleDesc.Quality = 0;

	if (FAILED(DEVICE->CreateTexture2D(&m_Tex2DDesc, nullptr, m_Tex2D.GetAddressOf())))
	{
		return E_FAIL;
	}

	// Create View Corresponding to _bindFlag
	if (m_Tex2DDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
	{
		if (FAILED(DEVICE->CreateShaderResourceView(m_Tex2D.Get(), nullptr, m_SRV.GetAddressOf())))
		{
			return E_FAIL;
		}
	}
	if (m_Tex2DDesc.BindFlags & D3D11_BIND_UNORDERED_ACCESS)
	{
		if (FAILED(DEVICE->CreateUnorderedAccessView(m_Tex2D.Get(), nullptr, m_UAV.GetAddressOf())))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

