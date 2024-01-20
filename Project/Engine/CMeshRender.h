#pragma once
#include "CRenderComponent.h"
class CMeshRender :
    public CRenderComponent
{
public:
    CMeshRender();
    ~CMeshRender();

    CLONE(CMeshRender);

public:
    void CompRender() override;
};