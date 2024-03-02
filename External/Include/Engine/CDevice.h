#pragma once

#include "ptr.h"
#include "CTexture.h"
#include "CConstBuffer.h"

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
	ComPtr<ID3D11Texture2D> m_RTTex;  // 역할이 정해져 있는게 명확한 변수인데 모든 view 를 다 가지고 있는 CTexture 를 사용할 필요가 있나/

	//Ptr<CTexture> m_RTTex;

	ComPtr<ID3D11RenderTargetView> m_RTV;
	ComPtr<ID3D11Texture2D> m_DSTex;
	//Ptr<CTexture> m_DSTex;
	ComPtr<ID3D11DepthStencilView> m_DSV;

	// Sampler
	ComPtr<ID3D11SamplerState> m_Sampler[2];

	// RasterizerState
	ComPtr<ID3D11RasterizerState> m_RSState[(UINT)RS_TYPE::END];

	// DepthStencilState
	ComPtr<ID3D11DepthStencilState> m_DSState[(UINT)DS_TYPE::END];

	// BlendState
	ComPtr<ID3D11BlendState> m_BState[(UINT)BS_TYPE::END];

	// 렌더타겟 해상도
	Vec2 m_vRTResolution;

	// 상수 버퍼
	CConstBuffer* m_arrConstBuffer[(UINT)CB_TYPE::END];

public:
	HRESULT DeviceInit(HWND _hWnd, UINT _width, UINT _height);
	void ClearTarget();
	void OMSet() { m_Context->OMSetRenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get()); }
	void Present() { m_SwapChain->Present(0, 0); }

	CConstBuffer* GetConstBuffer(CB_TYPE _type);

private:
	HRESULT CreateSwapChain();
	HRESULT CreateView();
	HRESULT CreateRasterizerState();
	HRESULT CreateDepthStencilState();
	HRESULT CreateBlendState();
	HRESULT CreateSampler();
	void CreateConstBuffers();

public:
	ID3D11Device* GetDevice() { return m_Device.Get(); }
	ID3D11DeviceContext* GetDeviceContext() { return m_Context.Get(); }
	Vec2 GetRTResolution() { return m_vRTResolution; }

	ComPtr<ID3D11RasterizerState> GetRSState(RS_TYPE _Type) { return m_RSState[(UINT)_Type]; }
	ComPtr<ID3D11DepthStencilState> GetDSState(DS_TYPE _Type) { return m_DSState[(UINT)_Type]; }
	ComPtr<ID3D11BlendState> GetBState(BS_TYPE _Type) { return m_BState[(UINT)_Type]; }
};

