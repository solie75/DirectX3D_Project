#pragma once
#include "CLevel.h"
#include "CCamera.h"

class CLevel_Test1 :
	public CLevel
{
private:
	CCamera* m_pCamera;
public:
	CLevel_Test1();
	virtual ~CLevel_Test1();

	void LevelInit() override;
	void LevelTick() override;
	void LevelFinaltick() override;
	void LevelRender() override;
};

