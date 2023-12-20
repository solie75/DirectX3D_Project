#include "pch.h"
#include "CDevice.h"

CDevice::CDevice()
    : m_hWnd(nullptr)
    , m_ViewPort{}
{

}

CDevice::~CDevice()
{

}

HRESULT CDevice::DeviceInit(HWND _hWnd, UINT _width, UINT _height)
{
    m_hWnd = _hWnd;
    m_vRTResolution = Vector2(_width, _height);

    int iFlag = 0;
#ifdef _DEBUG
    iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

    // Create Device, Context
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

    if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE
        , nullptr, iFlag, nullptr, 0, D3D11_SDK_VERSION
        , m_Device.GetAddressOf(), &featureLevel, m_Context.GetAddressOf())))
    {
        MessageBox(nullptr, L"Device, Context 생성 실패", L"Device 초기화 오류", MB_OK);
        return E_FAIL;
    }

    if (FAILED(CreateSwapChain()))
    {
        MessageBox(nullptr, L"SwapChain 생성 실패", L"Device 초기화 오류", MB_OK);
        return E_FAIL;
    }

    if (FAILED(CreateView()))
    {
        MessageBox(nullptr, L"view 생성 실패", L"LDevice 초기화 에러", MB_OK);
        return E_FAIL;
    }


    // ViewPort 설정
    m_ViewPort.TopLeftX = 0.f;
    m_ViewPort.TopLeftY = 0.f;

    m_ViewPort.Width = m_vRTResolution.x;
    m_ViewPort.Height = m_vRTResolution.y;

    m_ViewPort.MinDepth = 0.f;
    m_ViewPort.MaxDepth = 1.f;

    m_Context->RSSetViewports(1, &m_ViewPort);

    // ResterizerState 생성
    //if (FAILED(CreateRasterizerState()))
    //{
    //    MessageBox(nullptr, L"Rasterizer State 생성 실패", L"Device 초기화 오류", MB_OK);
    //    return E_FAIL;
    //}

    //// DepthStencilState 생성
    //if (FAILED(CreateDepthStencilState()))
    //{
    //    MessageBox(nullptr, L"DepthStencil State 생성 실패", L"Device 초기화 오류", MB_OK);
    //    return E_FAIL;
    //}

    //// BlendState 생성
    //if (FAILED(CreateBlendState()))
    //{
    //    MessageBox(nullptr, L"Blend State 생성 실패", L"Device 초기화 오류", MB_OK);
    //    return E_FAIL;
    //}

    //// Sampler 생성
    //if (FAILED(CreateSampler()))
    //{
    //    MessageBox(nullptr, L"Sampler 생성 실패", L"Device 초기화 오류", MB_OK);
    //    return E_FAIL;
    //}

    return S_OK;
}

void CDevice::ClearTarget()
{
    FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

    m_Context->ClearRenderTargetView(m_RTV.Get(), bgColor);
    m_Context->ClearDepthStencilView(m_DSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_Context->OMSet
        
        RenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get());

    m_SwapChain->Present(0,0);
}

HRESULT CDevice::CreateSwapChain()
{
    // SwapChain 설정
    DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};

    SwapChainDesc.OutputWindow = m_hWnd;    // 출력 윈도우
    SwapChainDesc.Windowed = true;          // 창모드, 전체화면 모드
    
    SwapChainDesc.BufferCount = 1;
    SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    SwapChainDesc.BufferDesc.Width = (UINT)m_vRTResolution.x;
    SwapChainDesc.BufferDesc.Height = (UINT)m_vRTResolution.y;
    SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    
    SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
    
    SwapChainDesc.SampleDesc.Count = 1;
    SwapChainDesc.SampleDesc.Quality = 0;
    SwapChainDesc.Flags = 0;

    // SwapChain 생성
    ComPtr<IDXGIDevice> pDXGIDevice;
    ComPtr<IDXGIAdapter> pAdapter;
    ComPtr<IDXGIFactory> pFactory;

    HRESULT hr = S_OK;
    hr = m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf());
    hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf());
    hr = pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());
    hr = pFactory->CreateSwapChain(m_Device.Get(), &SwapChainDesc, m_SwapChain.GetAddressOf());

    return hr;
}

HRESULT CDevice::CreateView()
{
    // RenderTarget 용 텍스쳐 등록
    ComPtr<ID3D11Texture2D> tTex2D;
    m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)tTex2D.GetAddressOf());
    if (FAILED(m_Device->CreateRenderTargetView(tTex2D.Get(), nullptr, m_RTV.GetAddressOf())))
    {
        return E_FAIL;
    }

    // DepthStencil 용 텍스쳐 등록
    D3D11_TEXTURE2D_DESC TexDesc;
    TexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    TexDesc.Width = m_vRTResolution.x;
    TexDesc.Height = m_vRTResolution.y;
    TexDesc.ArraySize = 1;

    TexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    TexDesc.Usage = D3D11_USAGE_DEFAULT;
    TexDesc.CPUAccessFlags = 0;
    TexDesc.SampleDesc.Count = 1;
    TexDesc.SampleDesc.Quality = 0;

    TexDesc.MiscFlags = 0;
    TexDesc.MipLevels = 1;

    if (FAILED(m_Device->CreateTexture2D(&TexDesc, nullptr, tTex2D.GetAddressOf())))
    {
        return E_FAIL;
    }

    if (FAILED(m_Device->CreateDepthStencilView(tTex2D.Get(), nullptr, m_DSV.GetAddressOf())))
    {
        return E_FAIL;
    }

    return S_OK;
}

//HRESULT CDevice::CreateRasterizerState()
//{
//    return E_NOTIMPL;
//}
//
//HRESULT CDevice::CreateDepthStencilState()
//{
//    return E_NOTIMPL;
//}
//
//HRESULT CDevice::CreateBlendState()
//{
//    return E_NOTIMPL;
//}
//
//HRESULT CDevice::CreateSampler()
//{
//    return E_NOTIMPL;
//}
