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
	// ������ �ִϸ��̼��� �̹� �����ϴ� �� Ȯ��
	std::map<std::wstring, CAnimation2D*>::iterator iter = m_mapAni2D.find(_strAniName);

	// FindAnimatinon And AddAnimation
	if (iter != m_mapAni2D.end())
	{
		MessageBox(nullptr, L"�̹� �����ϴ� 2D Animation �Դϴ�.", L"2D Animation ���� ����", MB_OK);

		if (S_OK == iter->second->FindAtlas(_strAniName))
		{
			MessageBox(nullptr, L"�̹� �����ϴ� Atlas �Դϴ�.", L"Atlas �̹��� ���� ����", MB_OK);
			return;
		}

		return;
	}
	else // Create Animation
	{
		CAnimation2D* tempAni2D = new CAnimation2D(_strAniName);

		if (S_OK == tempAni2D->FindAtlas(_strAniName))
		{

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
		MessageBox(nullptr, L"�ش� �ִϸ��̼��� ���� ���� �ʽ��ϴ�.", L"Animation ���� ����", MB_OK);
		return;
	}

	// Change Current Animation
	m_pCurAni2D = iter->second;
	m_pCurAni2D->SetBoolLoop(_bLoop);
	
	// Set Texture of current Animation into MeshRender's member Texture
	CRenderComponent* tempMR = GetOwnerObj()->GetRenderComponent();
	Ptr<CMaterial> tempMT = tempMR->GetMaterial();
	tempMT->SetMtrlTexParam(MATERIAL_TEX_PARAM::TEX_0, m_pCurAni2D->GetAtlasTex());
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

