#pragma once
#include "CEntity.h"
#include "CComponent.h"

class CGameObject :
    public CEntity
{ 
private:
    bool m_bDead;
    CComponent* m_arrCom[(UINT)COMPONENT_TYPE::END]{};

public:
    CGameObject();
    CGameObject(const CGameObject& _other);
    ~CGameObject();

    CLONE(CGameObject);

public:
    void ObjInit();
    void ObjTick();
    void ObjFinaltick();
    void ObjRender();

    void AddComponent(CComponent* _component);
    CComponent* GetComponent(COMPONENT_TYPE _type);
};
