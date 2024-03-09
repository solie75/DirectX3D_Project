#pragma once
#include "CScript.h"
class CPlayerScript :
    public CScript
{
public:
    CPlayerScript();
    ~CPlayerScript();

    CLONE(CPlayerScript);

public:
    virtual void ScriptInit() override;
    virtual void ScriptTick() override;
    virtual void ScriptFinalTick() override;
    
    void PlayWalkAniWithPrevDir();
};

