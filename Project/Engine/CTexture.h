#pragma once
#include "CRes.h"

#include <DirectXTex/DirectXTex.h>

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex//DirectXTex_debug")
#else 
#pragma comment(lib, "DirectXTex//DirectXTex")
#endif

class CTexture :
    public CRes
{
private:
    ComPtr<ID3D11Texture2D> m_Tex2D;
    ComPtr<ID3D11ShaderResourceView> m_SRV;
    D3D11_TEXTURE2D_DESC m_Tex2DDesc;

    ScratchImage m_Image;

public:
    ComPtr<ID3D11Texture2D> GetTex2D() { return m_Tex2D; }
    //ComPtr<ID3D11RenderTargetView> GetRTV() { return m_RTV; }
    //ComPtr<ID3D11DepthStencilView> GetDSV() { return m_DSV; }

public:
    virtual HRESULT LoadRes(const wstring& _strFilePath) override;
    virtual HRESULT SaveRes(const wstring& _strFilePath) override;

    void UpdateTexData(int _iRegisterNum);

    static void ClearTexRegister(int _iRegisterNum); // 왜 static 으로 선언했을까?
    //void ClearAllTexRegister();
    
public:
    CTexture(bool _bEngine = false);
    ~CTexture();
};

 