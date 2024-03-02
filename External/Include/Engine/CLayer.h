#pragma once
#include "CEntity.h"
#include "CGameObject.h"


class CLayer :
    public CEntity
{
private:
    vector<CGameObject*> m_vecObj;
    LAYER_TYPE m_LayerType;

public:
    CLayer();
    ~CLayer();

    CLONE(CLayer);

public:
    void LayerInit(LAYER_TYPE _type);
    void LayerTick();
    void LayerFinaltick();
    //void LayerRender();

public:
    void AddGameObj(CGameObject* _obj);
    
    const vector<CGameObject*>& GetObjs();

    void ClearObj();
};

