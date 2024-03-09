#pragma once
#include "CTexture.h"
#include "ptr.h"
#include "CConstBuffer.h"

class CAnimator2D;

class CAnimation2D
{
public:
    CAnimation2D(const wstring _ani2DName);
    ~CAnimation2D();

    enum class ANI2D_EVENT_TYPE
    {
        START,
        COMPLETE,
        END,
    };

private:
    CAnimator2D* m_pOwner;

    Ptr<CTexture> m_AtlasTex;
    float m_fDurationPerSprite;
    float m_fAccumulateTime;
    bool m_bLoop;
    bool m_bLoopFinish;
    const wstring m_sAni2DName;
    tAnimation_CB m_tAniCB;

public:
    bool IsAnimFinish() { return m_bLoopFinish; }
    HRESULT FindAtlas(const wstring _atlasName);
    HRESULT FindSprite(const wstring _spriteName);
    void CreateAtlas(Vec2 _spriteSize, UINT _spriteNum, float _durationTime);
    //void CreateAtlas();
    void SaveAtlas();
    void LoadAtlas(const wstring& _atlasName);
    void LoadAnimationData(const wstring& _aniName);
    void Ani2DUpdate();
    void Ani2DLateUpdate();
    void Ani2DBind();
    Ptr<CTexture> GetAtlasTex();
    Ptr<CTexture> ChangeAtlasTex(const wstring& _aniName);
    void SetBoolLoop(bool _b);
    void SetAnimatorOwner(CAnimator2D* _animator) { m_pOwner = _animator; }
};

