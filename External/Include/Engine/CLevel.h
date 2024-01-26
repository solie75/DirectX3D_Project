#pragma once
#include "CEntity.h"
#include "CLayer.h"

class CLevel :
	public CEntity
{
private:
	CLayer* m_arrLayer[(UINT)LAYER_TYPE::END];
	LEVEL_TYPE m_CurLevelType;
public:
	CLevel(LEVEL_TYPE _type);
	~CLevel();

	CLONE(CLevel);

public:
	virtual void LevelInit();
	virtual void LevelTick();
	virtual void LevelFinaltick();
	virtual void LevelRender();

public:
	void AddGameObj(CGameObject* _Object, int _iLayerIdx);

	void ChangeLevel(LEVEL_TYPE _type);
	LEVEL_TYPE GetLevelType();

private:
	void ClearObj();
};

