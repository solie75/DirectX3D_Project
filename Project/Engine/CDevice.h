#pragma once

#include "ptr.h"

class CDevice
	: public CSingleton<CDevice>
{
	SINGLE(CDevice)
private:
	HWND m_hWnd;

	ComPtr<ID3D11Device> m_Device; // GPU 메모리 할당
	ComPtr<ID3D11DeviceContext> m_Context; // GPU 제어, 명령 수행, 렌더링 진행

	ComPtr<IDXGISwapChain> m_SwapChain;

	D3D11_VIEWPORT m_ViewPort;

	// Texture, View
	ComPtr<ID3D11Texture2D> m_RTTex;
	ComPtr<ID3D11RenderTargetView> m_RTV;
	ComPtr<ID3D11Texture2D> m_DSTes;
	ComPtr<ID3D11DepthStencilView> m_DSV;

	//// Sampler
	//ComPtr<ID3D11SamplerState> m_Sampler[2]; // 왜 2개? RT 와 DS 용으로 두개인가?

	//// RasterizerState
	//ComPtr<ID3D11RasterizerState> m_RState[(UINT)RS_TYPE::END];

	//// DepthStencilState
	//ComPtr<ID3D11DepthStencilState> m_DSState[(UINT)DS_TYPE::END];

	//// BlendState
	//ComPtr<ID3D11BlendState> m_BState[(UINT)BS_TYPE::END];

	// 렌더타겟 해상도
	Vec2 m_vRTResolution;

public:
	HRESULT DeviceInit(HWND _hWnd, UINT _width, UINT _height);
	void ClearTarget();
	void OMSet() { m_Context->OMSetRenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get()); }
	void Present() { m_SwapChain->Present(0, 0); }

private:
	HRESULT CreateSwapChain();
	HRESULT CreateView();
	//HRESULT CreateRasterizerState();
	//HRESULT CreateDepthStencilState();
	//HRESULT CreateBlendState();
	//HRESULT CreateSampler();

public:
	ID3D11Device* GetDevice() { return m_Device.Get(); }
	ID3D11DeviceContext* GetDeviceContext() { return m_Context.Get(); }
};

