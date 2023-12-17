#pragma once

#include "ptr.h"

class CDevice
	: public CSingleton<CDevice>
{
	SINGLE(CDevice)
private:
	HWND m_hWnd;

	ComPtr<ID3D11Device> m_Device; // GPU �޸� �Ҵ�
	ComPtr<ID3D11DeviceContext> m_Comtext; // GPU ����, ��� ����, ������ ����

	ComPtr<IDXGISwapChain> m_SwapChain;

	ptr<CTexture> m_RTTex;

};

