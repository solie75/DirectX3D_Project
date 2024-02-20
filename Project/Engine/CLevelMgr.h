#pragma once
#include "CLevel.h"
#include "CSingleton.h"

class CLevelMgr :
	public CSingleton<CLevelMgr>
{
	SINGLE(CLevelMgr);

private:
	CLevel* m_pCurLevel;

public:
	void LevelMgrInit();
	void LevelMgrTick();
	void LevelMgrFinalTick();
	void LevelMgrRender();

public:
	CLevel* GetCurLevel();
	void ChangeLevel(CLevel* _nextLevel);
};

