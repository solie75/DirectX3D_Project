#include "pch.h"
#include "CTimeMgr.h"
#include "CEngine.h"


CTimeMgr::CTimeMgr()
	: m_liPrevCount{}
	, m_liCurCount{}
	, m_liFrequency{}
	, m_iCallCount(0)
	, m_fDeltaTime(0.f)
	, m_fTime(0.f)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::TimeMgrInit()
{
	// 현재 시스템의 고해상도 타이머의 주파수(1초당 진동수)를 반환
	QueryPerformanceFrequency(&m_liFrequency);

	// 함수가 호출된 시점의 타이머(컴퓨터가 실행되고 시간의 지남 정도를 축적한다.) 값 반환
	QueryPerformanceCounter(&m_liCurCount);
	QueryPerformanceCounter(&m_liPrevCount);
}

void CTimeMgr::TimeMgrTick()
{
	QueryPerformanceCounter(&m_liCurCount);

	// Tick 사이 시간
	m_fDeltaTime = (float)(m_liCurCount.QuadPart - m_liPrevCount.QuadPart) / (float)(m_liFrequency.QuadPart);
	
	// 누적 시간
	m_fTime += m_fDeltaTime;

	//  함수 호출 횟수
	++m_iCallCount;

	// 이전 카운트 값을 현재 카운트로 갱신
	m_liPrevCount = m_liCurCount;

	// Set Global CB Data
	GlobalData.DeltaTime = m_fDeltaTime;
	GlobalData.AccumulateTime += m_fDeltaTime;
}

void CTimeMgr::TimeMgrRender()
{
	static wchar_t szBuff[256] = {};

	if (1.f <= m_fTime)
	{
		swprintf_s(szBuff, L"FPS : %d, DT : %f", m_iCallCount, m_fDeltaTime);
		SetWindowTextW(CEngine::GetInst()->GetMainWindowHandle(), szBuff);

		m_fTime = 0.f;
		m_iCallCount = 0;
	}
}

float CTimeMgr::GetDeltaTime()
{
	return m_fDeltaTime;
}
