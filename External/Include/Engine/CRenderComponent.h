#pragma once
#include "CComponent.h"

#include "CMesh.h"
#include "CMaterial.h"

class CRenderComponent :
    public CComponent
{
private:
    Ptr<CMesh> m_pMesh;
    Ptr<CMaterial> m_pMaterial;

public:
    CRenderComponent(COMPONENT_TYPE _type);
    ~CRenderComponent();

public:
    virtual void CompRender() = 0;
    //void CompRender() override;

public:
    void SetMesh(Ptr<CMesh> _mesh);
    void SetMaterial(Ptr<CMaterial> _mtrl);

    Ptr<CMesh> GetMesh();
    Ptr<CMaterial> GetMaterial();
};

