#include "pch.h"
#include "CLayer.h"

CLayer::CLayer()
    : m_vecObj{}
    , m_LayerType(LAYER_TYPE::END)
{
}

CLayer::~CLayer()
{
    Safe_Del_Vec(m_vecObj);
}

void CLayer::LayerInit()
{
    for (size_t i = 0; i < m_vecObj.size(); ++i)
    {
        m_vecObj[i]->ObjInit();
    }
}

void CLayer::LayerTick()
{
    for (size_t i = 0; i < m_vecObj.size(); ++i)
    {
        m_vecObj[i]->ObjTick();
    }
}

void CLayer::LayerFinaltick()
{
    for (size_t i = 0; i < m_vecObj.size(); ++i)
    {
        m_vecObj[i]->ObjFinaltick();
    }
}

void CLayer::LayerRender()
{
    for (size_t i = 0; i < m_vecObj.size(); ++i)
    {
        m_vecObj[i]->ObjRender();
    }
}

void CLayer::AddGameObj(CGameObject* _obj)
{
    m_vecObj.push_back(_obj);

}

const vector<CGameObject*>& CLayer::GetObjs()
{
    return m_vecObj;
}

void CLayer::ClearObj()
{
    m_vecObj.clear();
}
