#pragma once
#include "CRes.h"

#include <DirectXTex/DirectXTex.h>

class CTexture :
    public CRes
{
private:
    ComPtr<ID3D11Texture2D> m_Tex2D;
    ComPtr<ID3D11ShaderResourceView> m_SRV;
    ComPtr<ID3D11RenderTargetView> m_RTV;
    ComPtr<ID3D11DepthStencilView> m_DSV;
    ComPtr<ID3D11UnorderedAccessView> m_UAV;

    D3D11_TEXTURE2D_DESC m_TexDesc;
    ScratchImage m_Image;

    //UINT m_iRecentNum;

public:
    HRESULT Create(UINT _width, UINT _height, DXGI_FORMAT _pixelFormat
        , UINT _bindFlag, D3D11_USAGE _usage);

    HRESULT Create(ComPtr<ID3D11Texture2D> _tex2D);

public:
    float GetTexWidth() { return (float)m_TexDesc.Width; }
    float GetTexHeight() { return (float)m_TexDesc.Height; }

    ComPtr<ID3D11Texture2D> GetTex2D() { return m_Tex2D; }
    ComPtr<ID3D11ShaderResourceView> GetSRV() { return m_SRV; }
    ComPtr<ID3D11RenderTargetView> GetRTV() { return m_RTV; }
    ComPtr<ID3D11DepthStencilView> GetDSV() { return m_DSV; }
    ComPtr<ID3D11UnorderedAccessView> GetUAV() { return m_UAV; }

private:
    virtual HRESULT LoadRes(const wstring& _strFilePath) override;

public:
    virtual HRESULT SaveRes(const wstring& _strFilePath) override;


public:
    CTexture(bool _bEngine = false);
    ~CTexture();
};

