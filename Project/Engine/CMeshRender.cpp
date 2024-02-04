#include "pch.h"
#include "CMeshRender.h"
#include "CTransform.h"

CMeshRender::CMeshRender()
	: CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
	SetName(L"MeshRender");
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::CompRender()
{
	if (nullptr == GetMesh() || nullptr == GetMaterial())
	{
		return;
	}

	// Transform & Animation Update Part

	GetOtherComp<CTransform>(COMPONENT_TYPE::TRANSFORM)->TransUpdateData();

	// Material Update
	GetMaterial()->UpdateMtrlData();

	// Render
	GetMesh()->RenderMesh();
}
