#pragma once
#include "CComponent.h"
#include "CAnimation2D.h"

struct tAtlasData
{
    UINT SpriteNum;
    float TimePerSprite;
    Vec2 SpriteSize;
};

class CAnimator2D :
    public CComponent
{
public:
    CAnimator2D();
    ~CAnimator2D();

    CLONE(CAnimator2D);
private:
    vector<CAnimation2D*> m_vecAni2D;
    CAnimation2D* m_pCurAni2D;

public:
    //HRESULT FindAtlasFIle(const wstring& _strName);
    void CreateAnimation2D(const wstring& _strAniName, tAtlasData _atlasData); // ���Ŀ� tool é�Ϳ��� tool �� Animation create ����� �ű⵵�� �Ѵ�.
};