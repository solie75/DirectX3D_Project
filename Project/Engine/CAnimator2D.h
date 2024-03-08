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
    map <std::wstring, CAnimation2D*> m_mapAni2D;
    CAnimation2D* m_pCurAni2D;



public:
    //HRESULT FindAtlasFIle(const wstring& _strName);
    void CreateAni2D(const wstring& _strAniName, tAtlasData _atlasData); // ���Ŀ� tool é�Ϳ��� tool �� Animation create ����� �ű⵵�� �Ѵ�.
    void PlayAni2D(const wstring& _aniName, bool _bLoop);
    void FindAni2D(const wstring& _aniName);

    virtual void CompInit() override;
    virtual void CompTick() override;
    virtual void CompFinalTick() override;
};