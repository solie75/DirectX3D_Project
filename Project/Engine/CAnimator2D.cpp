#include "pch.h"
#include "CAnimator2D.h"
#include "CMeshRender.h"

CAnimator2D::CAnimator2D()
	: CComponent(COMPONENT_TYPE::ANIMATOR2D)
{
}

CAnimator2D::~CAnimator2D()
{
}


void CAnimator2D::CreateAni2D(const wstring& _strAniName, tAtlasData _atlasData)
{
	// 기존에 애니메이션이 이미 존재하는 지 확인
	std::map<std::wstring, CAnimation2D*>::iterator iter = m_mapAni2D.find(_strAniName);

	// FindAnimatinon And AddAnimation
	if (iter != m_mapAni2D.end())
	{
		MessageBox(nullptr, L"이미 존재하는 2D Animation 입니다.", L"2D Animation 존재 여부", MB_OK);

		if (S_OK == iter->second->FindAtlas(_strAniName))
		{
			MessageBox(nullptr, L"이미 존재하는 Atlas 입니다.", L"Atlas 이미지 존재 여부", MB_OK);
			return;
		}

		return;
	}
	else // Create Animation
	{
		CAnimation2D* tempAni2D = new CAnimation2D(_strAniName);

		tempAni2D->LoadAnimationData(_strAniName);
		if (S_OK == tempAni2D->FindAtlas(_strAniName))
		{
			tempAni2D->LoadAtlas(_strAniName);
		}
		else
		{
			tempAni2D->CreateAtlas(_atlasData.SpriteSize, _atlasData.SpriteNum, _atlasData.TimePerSprite);
		}

		m_mapAni2D.insert(make_pair(_strAniName, tempAni2D));
		tempAni2D->SetAnimatorOwner(this);
	}
}

void CAnimator2D::PlayAni2D(const wstring& _aniName, bool _bLoop)
{
	// Check if Animation exist
	std::map<std::wstring, CAnimation2D*>::iterator iter = m_mapAni2D.find(_aniName);
	
	if (iter == m_mapAni2D.end())
	{
		MessageBox(nullptr, L"해당 애니메이션이 존재 하지 않습니다.", L"Animation 존재 여부", MB_OK);
		return;
	}

	// Change Current Animation
	m_pCurAni2D = iter->second;
	m_pCurAni2D->SetBoolLoop(_bLoop);
	
	// Set Texture of current Animation into MeshRender's member Texture
	CRenderComponent* tempMR = GetOwnerObj()->GetRenderComponent();
	Ptr<CMaterial> tempMT = tempMR->GetMaterial();

	// 현재는 하나의 애니메이션이 하나의 Ani Data 와 Atlas Texture 를 가지고 있다.
	// 따라서 플레이 하고자 하는 애니메이션에 대해서 Ani Data 와 Atlas Texture 를 그에 맞게 변경해주어야한다.
	// 이는 애니메이션의 종류가 변경될 때마다 변경 연상이 필요하게 된다. 이것이 자원을 많이 잡아먹는다고 판단되면 
	// Atlas Texture 를 모두 Animatino 이 std::map 으로 가지고 있는 방법을 생각해 볼것
	tempMT->SetMtrlTexParam(MATERIAL_TEX_PARAM::TEX_0, m_pCurAni2D->ChangeAtlasTex(_aniName));
}

void CAnimator2D::CompInit()
{
}

void CAnimator2D::CompTick()
{
	m_pCurAni2D->Ani2DUpdate();
}

void CAnimator2D::CompFinalTick()
{
	m_pCurAni2D->Ani2DLateUpdate();
}

