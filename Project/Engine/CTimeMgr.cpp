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
	// ���� �ý����� ���ػ� Ÿ�̸��� ���ļ�(1�ʴ� ������)�� ��ȯ
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
