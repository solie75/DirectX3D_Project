#pragma once

class CEngine
	: public CSingleton<CEngine>
{
	SINGLE(CEngine)

private:
	HWND m_hWnd;

	Vec2 m_vResolution;

public:
	Vec2 GetWindowResolution() { return m_vResolution; }
	HWND GetMainWindowHandle() { return m_hWnd; }

public:
	int EngineInit(HWND _hWnd, UINT _iWidth, UINT _iHeight);
	void EngineProgress();

private:
	void EngineTick();
	void EngineRender();
};


