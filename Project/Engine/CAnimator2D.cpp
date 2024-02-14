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
			MessageBox(nullptr, L"�̹� �����ϴ� Atlas �Դϴ�.", L"Atlas �̹��� ���� ����", MB_OK);
			return;
		}
	}

	// �ش� Atlas �� ���� ���� �ʴ� ���
	CAnimation2D* tempAni2D = new CAnimation2D(_strAniName);
	tempAni2D->CreateAtlas(_atlasData.SpriteSize, _atlasData.SpriteNum);
}
