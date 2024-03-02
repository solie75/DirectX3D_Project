#include "pch.h"
#include "CLevelMgr.h"
#include "CKeyMgr.h"
#include "CLevel_Test1.h"
#include "CLevel_Test2.h"

CLevelMgr::CLevelMgr()
    : m_pCurLevel(nullptr)
{
}

CLevelMgr::~CLevelMgr()
{
    if (nullptr != m_pCurLevel)
    {
        delete m_pCurLevel;
    }
}

void CLevelMgr::LevelMgrInit()
{
    m_pCurLevel = new CLevel_Test1;
    m_pCurLevel->LevelInit();
}

void CLevelMgr::LevelMgrTick()
{
    if (CKeyMgr::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
    {
        if (m_pCurLevel->GetLevelType() == LEVEL_TYPE::LEVEL_TYPE_TEST1)
        {
            ChangeLevel(new CLevel_Test2);
        }
        else if (m_pCurLevel->GetLevelType() == LEVEL_TYPE::LEVEL_TYPE_TEST2)
        {
            ChangeLevel(new CLevel_Test1);
        }
    }

    m_pCurLevel->LevelTick();

}

void CLevelMgr::LevelMgrFinalTick()
{
    m_pCurLevel->LevelFinaltick();
}

//void CLevelMgr::LevelMgrRender()
//{
//    m_pCurLevel->LevelRender();
//}

CLevel* CLevelMgr::GetCurLevel()
{
    return m_pCurLevel;
}

void CLevelMgr::ChangeLevel(CLevel* _nextLevel)
{
    if (nullptr != m_pCurLevel)
    {
        delete m_pCurLevel;
        m_pCurLevel = nullptr;
    }
    m_pCurLevel = _nextLevel;
    m_pCurLevel->LevelInit();
}
