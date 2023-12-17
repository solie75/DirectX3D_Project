#pragma once

#include "ptr.h"

class CDevice
	: public CSingleton<CDevice>
{
	SINGLE(CDevice)
private:
	HWND m_hWnd;

	ComPtr<ID3D11Device> m_Device; // GPU 메모리 할당
	ComPtr<ID3D11DeviceContext> m_Comtext; // GPU 제어, 명령 수행, 렌더링 진행

	ComPtr<IDXGISwapChain> m_SwapChain;

	ptr<CTexture> m_RTTex;

};

