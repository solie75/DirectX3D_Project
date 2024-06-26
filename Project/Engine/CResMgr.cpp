#include "pch.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CSetColorShader.h"

CResMgr::CResMgr()
{
}

CResMgr::~CResMgr()
{
}

void CResMgr::ResMgrInit()
{
	CreateDefaultMesh();
	CreateDefaultGraphicShader();
	CreateDefaultComputeShader();
	LoadDefaultTexture();
	CreateDefaultMaterial();
}

void CResMgr::ResMgrTick()
{
}

void CResMgr::CreateDefaultMesh()
{
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v;

	Ptr<CMesh> pMesh = nullptr;


	// ==============
	// PointMesh 생성
	// ==============
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vUV = Vec2(0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	UINT idx = 0;

	pMesh = new CMesh(true);
	
	pMesh->CreateMesh(&v, 1, &idx, 1);
	
	AddRes(L"PointMesh", pMesh);

	// =============
	// RectMesh 생성
	// =============
	// 0 --- 1 
	// |  \  |
	// 3 --- 2
	v.vPos = Vec3(-0.5f, 0.5f, 0.f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, 0.5f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	v.vUV = Vec2(1.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, -0.5f, 0.f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	v.vUV = Vec2(1.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(-0.5f, -0.5f, 0.f);
	v.vColor = Vec4(0.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 1.f);
	vecVtx.push_back(v);

	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);

	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);

	pMesh = new CMesh(true);
	pMesh->CreateMesh(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddRes(L"RectMesh", pMesh);

	vecIdx.clear();
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);
	vecIdx.push_back(3);
	vecIdx.push_back(0);

	pMesh = new CMesh(true);
	pMesh->CreateMesh(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddRes(L"RectMesh_Debug", pMesh);

	vecVtx.clear();
	vecIdx.clear();

	// ===========
	// Circle Mesh
	// ===========
	//      3 
	//   4     2
	//  5 --0-- 1
	float fRadius = 0.5f;
	UINT Slice = 40;
	float fTheta = XM_2PI / (float)Slice;

	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vUV = Vec2(0.5f, 0.5f);
	vecVtx.push_back(v);

	// set vertex pos
	for (UINT i = 0; i < Slice; ++i)
	{
		v.vPos = Vec3(fRadius * cosf(fTheta * (float)i), fRadius * sinf(fTheta * (float)i), 0.f);
		v.vUV = Vec2(v.vPos.x + 0.5f, -v.vPos.y + 0.5f);
		vecVtx.push_back(v);
	}

	// set idx
	for (UINT i = 0; i < Slice - 1; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	// last triangle
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(Slice);

	pMesh = new CMesh(true);
	pMesh->CreateMesh(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddRes(L"CircleMesh", pMesh);

	vecIdx.clear();
	for (UINT i = 0; i < Slice; ++i)
	{
		vecIdx.push_back(i + 1);
	}
	vecIdx.push_back(1);

	pMesh = new CMesh(true);
	pMesh->CreateMesh(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddRes(L"CircleMesh_Debug", pMesh);

	vecVtx.clear();
	vecIdx.clear();
}

void CResMgr::CreateDefaultGraphicShader()
{
	Ptr<CGraphicsShader> pShader = nullptr;
	
	// ============================
	// Std2DShader
	// RasterizerState      : None
	// BlendState           : Mask
	// DepthStencilState    : Less
	// ============================
	pShader = new CGraphicsShader();
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::MASK);

	AddRes(L"Std2DShader", pShader);

	// ============================
	// Animation2D Shader
	// RasterizerState      : None
	// BlendState           : Mask
	// DepthStencilState    : Less
	// ============================

	pShader = new CGraphicsShader();
	pShader->CreateVertexShader(L"shader\\Animation2D.fx", "VS_Ani2D");
	pShader->CreatePixelShader(L"shader\\Animation2D.fx", "PS_Ani2D");
	
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::MASK);

	AddRes(L"Ani2DShader", pShader);

	// =================
	// DebugShape Shader
	// Topology : LineStrip
	// RS_TYPE  : CULL_NONE
	// DS_TYPE  : NO_TEST_NO_WRITE
	// BS_TYPE  : Default
	// g_vec4_0 : OutColor
	// ==================
	pShader = new CGraphicsShader();
	pShader->CreateVertexShader(L"shader\\debug_shape.fx", "VS_DebugShape");
	pShader->CreatePixelShader(L"shader\\debug_shape.fx", "PS_DebugShape");

	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetBSType(BS_TYPE::DEFAULT);
	pShader->SetDomain(DOMAIN_TYPE::DOMAIN_MASK);

	AddRes(L"DebugShapeShader", pShader);

	// ============================
	// ParticleRender
	// 
	// RS_TYPE : CULL_NONE
	// DS_TYPE : NO_WRITE
	// BS_TYPE : ALPHA_BLEND

	// Parameter
	// g_int_0 : Particle Index
	// 
	// Domain : TRANSPARENT
	// ============================
	pShader = new CGraphicsShader;
	pShader->SetKey(L"ParticleRenderShader");
	pShader->CreateVertexShader(L"shader\\particle_render.fx", "VS_ParticleRender");
	pShader->CreateGeometryShader(L"shader\\particle_render.fx", "GS_ParticleRender");
	pShader->CreatePixelShader(L"shader\\particle_render.fx", "PS_ParticleRender");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_WRITE);
	pShader->SetBSType(BS_TYPE::ALPHA_BLEND);
	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	pShader->SetDomain(DOMAIN_TYPE::DOMAIN_TRANSPARENT);

	AddRes(pShader->GetKey(), pShader);
}

void CResMgr::CreateDefaultComputeShader()
{
	Ptr<CComputeShader> pCS = nullptr;

	pCS = new CSetColorShader(32, 32, 1);
	pCS->SetName(L"SetColorCS");
	pCS->CreateComputeShader(L"shader\\setColor.fx", "CS_SetColor");
	AddRes(pCS->GetName(), pCS);
}

void CResMgr::CreateDefaultMaterial()
{
	// Create Material
	Ptr<CMaterial> tempMtrl = nullptr;
	tempMtrl = new CMaterial();

	// Set Shader
	tempMtrl->SetShader(FindRes<CGraphicsShader>(L"Std2DShader"));

	// Set Texture
	tempMtrl->SetMtrlTexParam(TEX_0, FindRes<CTexture>(L"Fighter"));

	// Add Material to ResMgr
	AddRes(L"DefaultMtrl1", tempMtrl);

	Ptr<CMaterial> tempMtrl2 = nullptr;
	tempMtrl2 = new CMaterial();

	tempMtrl2->SetShader(FindRes<CGraphicsShader>(L"Std2DShader"));
	tempMtrl2->SetMtrlTexParam(TEX_1, FindRes<CTexture>(L"Link"));

	AddRes(L"DefaultMtrl2", tempMtrl2);
	
	// Animation 2d Mtrl
	tempMtrl = new CMaterial();
	tempMtrl->SetShader(FindRes<CGraphicsShader>(L"Ani2DShader"));
	AddRes(L"Ain2DMtrl", tempMtrl);


	// debug shape material
	tempMtrl = new CMaterial();
	tempMtrl->SetShader(FindRes<CGraphicsShader>(L"DebugShapeShader"));
	AddRes(L"DebugShapeMtrl", tempMtrl);

	// Particle Render Material
	tempMtrl = new CMaterial();
	tempMtrl->SetShader(FindRes<CGraphicsShader>(L"ParticleRenderShader"));
	AddRes(L"ParticleRenderMtrl", tempMtrl);
}

void CResMgr::LoadDefaultTexture()
{
	wstring strContent = CPathMgr::GetInst()->GetContentPath();
	wstring strFilePath1 = strContent + L"Texture\\Fighter.bmp";
	Ptr<CTexture> pRes1 = new CTexture;
	pRes1->SetRelativePath(L"Texture\\Fighter.bmp");
	pRes1->LoadRes(strFilePath1);

	AddRes(L"Fighter", pRes1);

	Ptr<CTexture> pRes2 = new CTexture; // 여기에서 new CTexture 를 새로 지정하지 않으면 pRes1 에 Link 가 저장된다.

	wstring strFilePath2 = strContent + L"Texture\\Link.png";
	pRes2->SetRelativePath(L"Texture\\Link.png");
	pRes2->LoadRes(strFilePath2);

	AddRes(L"Link", pRes2);

	// 여기에서 렌더링 단계에 바인딩
	//((CTexture*)pRes.Get())->UpdateTexData(0); // -> CMaterial의 UpdateMtrlData() 함수에서 진행된다.
}

void CResMgr::DeleteRes(RES_TYPE _type, const wstring& _strKey)
{
	map<wstring, Ptr<CRes>>::iterator iter = m_arrRes[(UINT)_type].find(_strKey);
	assert(!(iter == m_arrRes[(UINT)_type].end()));
	m_arrRes[(UINT)_type].erase(_strKey);
}
