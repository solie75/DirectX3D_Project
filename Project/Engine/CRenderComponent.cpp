#include "pch.h"
#include "CRenderComponent.h"

CRenderComponent::CRenderComponent(COMPONENT_TYPE _type)
    : CComponent(_type)
{
}

CRenderComponent::~CRenderComponent()
{
}

void CRenderComponent::SetMesh(Ptr<CMesh> _mesh)
{
    m_pMesh = _mesh;
}

void CRenderComponent::SetMaterial(Ptr<CMaterial> _mtrl)
{
    m_pMaterial = _mtrl;
}

Ptr<CMesh> CRenderComponent::GetMesh()
{
    return m_pMesh;
}

Ptr<CMaterial> CRenderComponent::GetMaterial()
{
    return m_pMaterial;
}
