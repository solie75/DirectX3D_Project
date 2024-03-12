#pragma once
#include "CScript.h"
class CPlayerScript :
    public CScript
{
public:
    CPlayerScript();
    ~CPlayerScript();

    CLONE(CPlayerScript);

private:
    vector<DIRECTION_TYPE> m_vecDir;

public:
    virtual void ScriptInit() override;
    virtual void ScriptTick() override;
    virtual void ScriptFinalTick() override;
    
    void PlayWalkAniWithPrevDir(DIRECTION_TYPE _type);
    void EraseDir(DIRECTION_TYPE _type);
};

