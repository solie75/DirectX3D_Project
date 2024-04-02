#include "pch.h"
#include "CDevice.h"

CDevice::CDevice()
    : m_hWnd(nullptr)
    , m_ViewPort{}
    , m_arrConstBuffer{}
{

}

CDevice::~CDevice()
{
    Safe_Del_Array(m_arrConstBuffer);
}

HRESULT CDevice::DeviceInit(HWND _hWnd, UINT _width, UINT _height)
{
    m_hWnd = _hWnd;
    m_vRTResolution = Vector2(_width, _height);

    GlobalData.Resolution = m_vRTResolution;

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
    if (FAILED(CreateRasterizerState()))
    {
        MessageBox(nullptr, L"Rasterizer State 생성 실패", L"Rasterizer State 초기화 오류", MB_OK);
        return E_FAIL;
    }

    // DepthStencilState 생성
    if (FAILED(CreateDepthStencilState()))
    {
        MessageBox(nullptr, L"DepthStencil State 생성 실패", L"DepthStencil State 초기화 오류", MB_OK);
        return E_FAIL;
    }

    // BlendState 생성
    if (FAILED(CreateBlendState()))
    {
        MessageBox(nullptr, L"Blend State 생성 실패", L"Blend State 초기화 오류", MB_OK);
        return E_FAIL;
    }

    // Sampler 생성
    if (FAILED(CreateSampler()))
    {
        MessageBox(nullptr, L"Sampler 생성 실패", L"Sampler 초기화 오류", MB_OK);
        return E_FAIL;
    }

    // ConstantBuffer Init
    CreateConstBuffers();

    return S_OK;
}

void CDevice::ClearTarget()
{
    FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

    m_Context->ClearRenderTargetView(m_RTV.Get(), bgColor);
    m_Context->ClearDepthStencilView(m_DSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

CConstBuffer* CDevice::GetConstBuffer(CB_TYPE _type)
{
    return m_arrConstBuffer[(UINT)_type];
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
    m_RTTex = tTex2D;
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
    m_DSTex = tTex2D;
    if (FAILED(m_Device->CreateDepthStencilView(tTex2D.Get(), nullptr, m_DSV.GetAddressOf())))
    {
        return E_FAIL;
    }

    return S_OK;
}

HRESULT CDevice::CreateRasterizerState()
{
    m_RSState[(UINT)RS_TYPE::CULL_BACK] = nullptr;

    D3D11_RASTERIZER_DESC Desc = {};
    Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
    Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    DEVICE->CreateRasterizerState(&Desc, m_RSState[(UINT)RS_TYPE::CULL_FRONT].GetAddressOf());

    Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
    Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    DEVICE->CreateRasterizerState(&Desc, m_RSState[(UINT)RS_TYPE::CULL_NONE].GetAddressOf());

    Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
    Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
    DEVICE->CreateRasterizerState(&Desc, m_RSState[(UINT)RS_TYPE::WIRE_FRAME].GetAddressOf());

    return S_OK;
}

HRESULT CDevice::CreateDepthStencilState()
{
    // Less
    D3D11_DEPTH_STENCIL_DESC Desc = {};
    Desc.DepthEnable = true;
    Desc.DepthFunc = D3D11_COMPARISON_LESS;
    Desc.StencilEnable = false;
    Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::LESS].GetAddressOf());

    // Less Equal
    Desc.DepthEnable = true;
    Desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    Desc.StencilEnable = false;
    Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::LESS_EQUAL].GetAddressOf());

    // Greater
    Desc.DepthEnable = true;
    Desc.DepthFunc = D3D11_COMPARISON_GREATER;
    Desc.StencilEnable = false;
    Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::GREATER].GetAddressOf());

    // Greater Equal
    Desc.DepthEnable = true;
    Desc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
    Desc.StencilEnable = false;
    Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::GREATER_EQUAL].GetAddressOf());

    // No Write
    Desc.DepthEnable = true;
    Desc.DepthFunc = D3D11_COMPARISON_LESS;
    Desc.StencilEnable = false;
    Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::NO_WRITE].GetAddressOf());

    // NoTest NoWrite
    Desc.DepthEnable = false;
    Desc.StencilEnable = false;
    Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::NO_TEST_NO_WRITE].GetAddressOf());

    return S_OK;
}

HRESULT CDevice::CreateBlendState()
{
    // No Blend
    m_BState[(UINT)BS_TYPE::DEFAULT] = nullptr;

    // Mask
    D3D11_BLEND_DESC Desc = {};
    Desc.AlphaToCoverageEnable = true;
    Desc.IndependentBlendEnable = false;

    Desc.RenderTarget[0].BlendEnable = true;
    Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
    Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;

    Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

    Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    DEVICE->CreateBlendState(&Desc, m_BState[(UINT)BS_TYPE::MASK].GetAddressOf());

    // Alpha Blend
    Desc.AlphaToCoverageEnable = false;
    Desc.IndependentBlendEnable = false;

    Desc.RenderTarget[0].BlendEnable = true;
    Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

    Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

    Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    DEVICE->CreateBlendState(&Desc, m_BState[(UINT)BS_TYPE::ALPHA_BLEND].GetAddressOf());

    // One One
    Desc.AlphaToCoverageEnable = false;
    Desc.IndependentBlendEnable = false;

    Desc.RenderTarget[0].BlendEnable = true;
    Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
    Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

    Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

    Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    DEVICE->CreateBlendState(&Desc, m_BState[(UINT)BS_TYPE::ONE_ONE].GetAddressOf());

    return S_OK;
}

HRESULT CDevice::CreateSampler()
{
    D3D11_SAMPLER_DESC tSamDesc = {};

    tSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    tSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    tSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    tSamDesc.Filter = D3D11_FILTER_ANISOTROPIC; // 축소시, 확대시, 밉맵간에 필터 처리를 전부 Anisotropic
    DEVICE->CreateSamplerState(&tSamDesc, m_Sampler[0].GetAddressOf());

    tSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    tSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    tSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    tSamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; // 축소시, 확대시, 밉맵간 필터처리 전부 point
    DEVICE->CreateSamplerState(&tSamDesc, m_Sampler[1].GetAddressOf());

    CONTEXT->VSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
    CONTEXT->PSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());

    CONTEXT->VSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
    CONTEXT->PSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());

    return S_OK;
}

void CDevice::CreateConstBuffers()
{
    m_arrConstBuffer[(UINT)CB_TYPE::TRANSFORM] = new CConstBuffer((UINT)CB_TYPE::TRANSFORM);
    m_arrConstBuffer[(UINT)CB_TYPE::TRANSFORM]->CreateCB(sizeof(tTransform_CB), 1);

    m_arrConstBuffer[(UINT)CB_TYPE::MATERIAL] = new CConstBuffer((UINT)CB_TYPE::MATERIAL);
    m_arrConstBuffer[(UINT)CB_TYPE::MATERIAL]->CreateCB(sizeof(tMtrl_CB), 1);

    m_arrConstBuffer[(UINT)CB_TYPE::ANIMATION2D] = new CConstBuffer((UINT)CB_TYPE::ANIMATION2D);
    m_arrConstBuffer[(UINT)CB_TYPE::ANIMATION2D]->CreateCB(sizeof(tAnimation_CB), 1);

    m_arrConstBuffer[(UINT)CB_TYPE::GLOBAL] = new CConstBuffer((UINT)CB_TYPE::GLOBAL);
    m_arrConstBuffer[(UINT)CB_TYPE::GLOBAL]->CreateCB(sizeof(tGlobal), 1);
}