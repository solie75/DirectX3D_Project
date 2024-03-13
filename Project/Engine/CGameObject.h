#pragma once
#include "CEntity.h"

class CComponent;
class CRenderComponent;
class CScript;

#define GET_COMPONENT(type, TYPE) C##type* Get##type() const {return (C##type*)m_arrComp[(UINT)COMPONENT_TYPE::TYPE]; }


class CGameObject :
    public CEntity
{
private:
    bool m_bDead;
    CComponent* m_arrComp[(UINT)COMPONENT_TYPE::END]{};
    CRenderComponent* m_pRenderComp;
    vector<CScript*> m_vecScript;

public:
    CGameObject();
    CGameObject(const CGameObject& _other);
    ~CGameObject();

    CLONE(CGameObject);

public:
    virtual void ObjInit();
    virtual void ObjTick();
    virtual void ObjFinaltick();
    virtual void ObjRender();

    void AddComponent(CComponent* _component);
    CComponent* GetComponent(COMPONENT_TYPE _type) { return m_arrComp[(UINT)_type]; }
    CRenderComponent* GetRenderComponent() { return m_pRenderComp; }

    bool IsDead() { return m_bDead; }

public:
    //GET_COMPONENT(Transform, TRANSFORM);

    template <typename T>
    T* GetComponent(COMPONENT_TYPE _type)
    {
        return (T*)m_arrComp[(UINT)_type];
    }
};

//template<typename T>
//inline T* CGameObject::GetComponent(COMPONENT_TYPE _type)
//{
//    return this->(T*)GetComponent(_type);
//}
