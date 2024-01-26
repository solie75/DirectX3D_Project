#pragma once
#include "CLevel.h"

class CLevel_Test1 :
	public CLevel
{
public:
	CLevel_Test1();
	virtual ~CLevel_Test1();

	void LevelInit() override;
	void LevelTick() override;
	void LevelFinaltick() override;
	void LevelRender() override;
};

