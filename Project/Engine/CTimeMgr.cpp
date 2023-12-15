#include "pch.h"
#include "CTimeMgr.h"

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
	QueryPerformanceCounter(&m_liCurCount);
	QueryPerformanceCounter(&m_liPrevCount);
}

void CTimeMgr::TimeMgrTick()
{
}

void CTimeMgr::TimeMgrRender()
{
}

float CTimeMgr::GetDeltaTime()
{
	return 0.0f;
}
