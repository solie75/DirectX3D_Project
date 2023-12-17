#include "pch.h"
#include "CTexture.h"

CTexture::CTexture(bool _bEngine)
    : CRes(RES_TYPE::TEXTURE, _bEngine)
    , m_TexDesc{}
{
}

CTexture::~CTexture()
{
}

HRESULT CTexture::Create(UINT _width, UINT _height, DXGI_FORMAT _pixelFormat, UINT _bindFlag, D3D11_USAGE _usage)
{
    // ID3D11Texture2D 생성
    m_TexDesc.Format = _pixelFormat;

    // render target 과 같은 해상도로 설정해야 한다.
    m_TexDesc.Width = _width;
    m_TexDesc.Height = _height;
    m_TexDesc.BindFlags = _bindFlag;
    m_TexDesc.Usage = _usage;

    // CPU가 resource 의 Data 를 자주 수정하는 경우
    if (D3D11_USAGE::D3D11_USAGE_DYNAMIC == _usage)
    {
        m_TexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    }
    // CPU 가 Resource 의 복사복을 읽어야 할 때 (Resource 가 data 를 비디오 RAM 에서 시스템 RAM 으로 전송할 수 있어야 할 때)
    else if (D3D11_USAGE::D3D11_USAGE_STAGING == _usage)
    {
        m_TexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    }

    m_TexDesc.MipLevels = 1; // 원본만 생성한다.
    m_TexDesc.SampleDesc.Count = 1;
    m_TexDesc.SampleDesc.Quality = 0;

    return S_OK;
}

HRESULT CTexture::Create(ComPtr<ID3D11Texture2D> _tex2D)
{
    return E_NOTIMPL;
}

HRESULT CTexture::LoadRes(const wstring& _strFilePath)
{
    return E_NOTIMPL;
}

HRESULT CTexture::SaveRes(const wstring& _strFilePath)
{
    return E_NOTIMPL;
}

