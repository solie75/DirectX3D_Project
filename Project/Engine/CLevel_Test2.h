#pragma once
#include "CLevel.h"
class CLevel_Test2 :
    public CLevel
{
public:
	CLevel_Test2();
	virtual ~CLevel_Test2();

	void LevelInit() override;
	void LevelTick() override;
	void LevelFinaltick() override;
	//void LevelRender() override;
};

