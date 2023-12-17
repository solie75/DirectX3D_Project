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
    // ID3D11Texture2D ����
    m_TexDesc.Format = _pixelFormat;

    // render target �� ���� �ػ󵵷� �����ؾ� �Ѵ�.
    m_TexDesc.Width = _width;
    m_TexDesc.Height = _height;
    m_TexDesc.BindFlags = _bindFlag;
    m_TexDesc.Usage = _usage;

    // CPU�� resource �� Data �� ���� �����ϴ� ���
    if (D3D11_USAGE::D3D11_USAGE_DYNAMIC == _usage)
    {
        m_TexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    }
    // CPU �� Resource �� ���纹�� �о�� �� �� (Resource �� data �� ���� RAM ���� �ý��� RAM ���� ������ �� �־�� �� ��)
    else if (D3D11_USAGE::D3D11_USAGE_STAGING == _usage)
    {
        m_TexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    }

    m_TexDesc.MipLevels = 1; // ������ �����Ѵ�.
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

