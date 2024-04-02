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
	// ���� �ý����� ���ػ� Ÿ�̸��� ���ļ�(1�ʴ� ������)�� ��ȯ
	QueryPerformanceFrequency(&m_liFrequency);

	// �Լ��� ȣ��� ������ Ÿ�̸�(��ǻ�Ͱ� ����ǰ� �ð��� ���� ������ �����Ѵ�.) �� ��ȯ
	QueryPerformanceCounter(&m_liCurCount);
	QueryPerformanceCounter(&m_liPrevCount);
}

void CTimeMgr::TimeMgrTick()
{
	QueryPerformanceCounter(&m_liCurCount);

	// Tick ���� �ð�
	m_fDeltaTime = (float)(m_liCurCount.QuadPart - m_liPrevCount.QuadPart) / (float)(m_liFrequency.QuadPart);
	
	// ���� �ð�
	m_fTime += m_fDeltaTime;

	//  �Լ� ȣ�� Ƚ��
	++m_iCallCount;

	// ���� ī��Ʈ ���� ���� ī��Ʈ�� ����
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
