#include "pch.h"
#include "CLevel.h"

CLevel::CLevel(LEVEL_TYPE _type)
	: m_arrLayer{}
	, m_CurLevelType(_type)
{
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		m_arrLayer[i] = new CLayer;
	}
}

CLevel::~CLevel()
{
	Safe_Del_Array(m_arrLayer);
}

void CLevel::LevelInit()
{
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		m_arrLayer[i]->LayerInit();
	}
}

void CLevel::LevelTick()
{
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		m_arrLayer[i]->LayerTick();
	}
}

void CLevel::LevelFinaltick()
{
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		m_arrLayer[i]->LayerFinaltick();
	}
}

void CLevel::LevelRender()
{
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		m_arrLayer[i]->LayerRender();
	}
}

void CLevel::AddGameObj(CGameObject* _Object, int _iLayerIdx)
{
	m_arrLayer[_iLayerIdx]->AddGameObj(_Object);
}

void CLevel::ChangeLevel(LEVEL_TYPE _type)
{
	m_CurLevelType = _type;
}

LEVEL_TYPE CLevel::GetLevelType()
{
	return m_CurLevelType;
}

void CLevel::ClearObj()
{
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		m_arrLayer[i]->ClearObj();
	}
}
