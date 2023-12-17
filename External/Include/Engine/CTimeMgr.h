#pragma once
class CTimeMgr
	: public CSingleton<CTimeMgr>
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_liPrevCount;
	LARGE_INTEGER m_liCurCount;
	LARGE_INTEGER m_liFrequency;

	UINT m_iCallCount;
	float m_fDeltaTime;
	float m_fTime;

public:
	void TimeMgrInit();
	void TimeMgrTick();
	void TimeMgrRender();

	float GetDeltaTime();
};

