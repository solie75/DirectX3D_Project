#include "pch.h"
#include "CEngine.h"

CEngine::CEngine()
    : m_hWnd(nullptr)
{
}

CEngine::~CEngine()
{
}

int CEngine::EngineInit(HWND _hWnd, UINT _iWidth, UINT _iHeight)
{
    m_hWnd = _hWnd;
    m_vResolution = Vec2((float)_iWidth, (float)_iHeight);

    RECT rt = { 0, 0, _iWidth, _iHeight };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
    SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
    ShowWindow(m_hWnd, true);

    return 0;
}

void CEngine::EngineProgress()
{
    EngineTick();
    EngineProgress();
}

void CEngine::EngineTick()
{
}

void CEngine::EngineRender()
{
}


