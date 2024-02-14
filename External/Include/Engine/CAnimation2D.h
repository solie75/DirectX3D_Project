#pragma once
#include "CTexture.h"
#include "ptr.h"

class CAnimator;

class CAnimation2D
{
public:
    CAnimation2D(const wstring _ani2DName);
    ~CAnimation2D();


private:
    CAnimator* m_pOwner;

    Ptr<CTexture> m_AtlasTex;
    float m_fDurationPerSprite;
    bool m_bLoop;
    bool m_bLoopFinish;
    UINT m_iCurSpriteNum;
    const wstring m_sAni2DName;
     
public:
    bool IsAnimFinish() { return m_bLoopFinish; }
    HRESULT FindAtlas(const wstring _atlasName);
    HRESULT FindSprite(const wstring _spriteName);
    void CreateAtlas(Vec2 _spriteSize, UINT _spriteNum);
    void SaveAtlas();
};

