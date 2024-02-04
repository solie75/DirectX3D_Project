#pragma once
#include "CEntity.h"
#include "CComponent.h"

class CTransform;
class CCamera;
class CMeshRender;

#define GET_COMPONENT(type, TYPE) C##type* Get##type() const {return (C##type*)m_arrCom[(UINT)COMPONENT_TYPE::TYPE]; }


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


public:
    //GET_COMPONENT(Transform, TRANSFORM);

    template <typename T>
    T* GetComponent(COMPONENT_TYPE _type);
};

template<typename T>
inline T* CGameObject::GetComponent(COMPONENT_TYPE _type)
{
    return this->(T*)m_arrCom[(UINT)_type];
}
