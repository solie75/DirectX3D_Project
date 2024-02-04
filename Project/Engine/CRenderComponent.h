#pragma once
#include "CComponent.h"

#include "CMesh.h"
#include "CMaterial.h"

class CRenderComponent :
    public CComponent
{
public:
    CRenderComponent(COMPONENT_TYPE _type);
    ~CRenderComponent();

private:
    Ptr<CMesh> m_pMesh;
    Ptr<CMaterial> m_pMaterial;

public:
    virtual void CompRender() = 0;

public:
    void SetMesh(Ptr<CMesh> _mesh);
    void SetMaterial(Ptr<CMaterial> _mtrl);

    Ptr<CMesh> GetMesh();
    Ptr<CMaterial> GetMaterial();
};

