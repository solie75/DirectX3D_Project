#include "pch.h"
#include "CAnimator2D.h"

CAnimator2D::CAnimator2D()
	: CComponent(COMPONENT_TYPE::ANIMATOR2D)
{
}

CAnimator2D::~CAnimator2D()
{
}


void CAnimator2D::CreateAnimation2D(const wstring& _strAniName, tAtlasData _atlasData)
{
	for (UINT i = 0; i < m_vecAni2D.size(); ++i)
	{
		if (S_OK == m_vecAni2D[i]->FindAtlas(_strAniName))
		{
			MessageBox(nullptr, L"이미 존재하는 Atlas 입니다.", L"Atlas 이미지 존재 여부", MB_OK);
			return;
		}
	}

	// 해당 Atlas 가 존재 하지 않는 경우
	CAnimation2D* tempAni2D = new CAnimation2D(_strAniName);
	tempAni2D->CreateAtlas(_atlasData.SpriteSize, _atlasData.SpriteNum);
}
