#include "pch.h"
#include "CResMgr.h"
#include "CMesh.h"
#include "CShader.h"

CResMgr::CResMgr()
{
}

CResMgr::~CResMgr()
{
}

void CResMgr::ResMgrInit()
{
	CreateDefaultMesh();
	CreateDefaultShader();
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
	// PointMesh 持失
	// ==============
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vUV = Vec2(0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	UINT idx = 0;

	pMesh = new CMesh(true);
	
	pMesh->CreateMesh(&v, 1, &idx, 1);
	
	AddRes(L"PointMesh", pMesh);

	// =============
	// RectMesh 持失
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

	vecVtx.clear();
	vecIdx.clear();
}

void CResMgr::CreateDefaultShader()
{
	Ptr<CShader> pShader = nullptr;
	
	// ============================
	// Std2DShader
	// RasterizerState      : None
	// BlendState           : Mask
	// DepthStencilState    : Less
	// ============================
	pShader = new CShader(RES_TYPE::SHADER);
	//pShader->SetKey(L"Std2DShader");
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D");

	AddRes(L"Std2DShader", pShader);

	Ptr<CShader> tempShader = nullptr;
	tempShader = new CShader(RES_TYPE::SHADER);
	tempShader = FindRes<CShader>(L"Std2DShader");
}

void CResMgr::DeleteRes(RES_TYPE _type, const wstring& _strKey)
{
	map<wstring, Ptr<CRes>>::iterator iter = m_arrRes[(UINT)_type].find(_strKey);
	assert(!(iter == m_arrRes[(UINT)_type].end()));
	m_arrRes[(UINT)_type].erase(_strKey);
}
