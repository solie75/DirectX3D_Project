#include "pch.h"
#include "CMeshRender.h"

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
	// ...

	// Material Update
	GetMaterial()->UpdateMtrlData();

	// Render
	GetMesh()->RenderMesh();
}
