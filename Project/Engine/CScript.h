#pragma once
#include "CComponent.h"

class CScript :
    public CComponent
{
public:
    CScript(SCRIPT_TYPE _iScriptType);
    ~CScript();

private:
    SCRIPT_TYPE m_iScriptType;

public:
    SCRIPT_TYPE GetScriptType() { return m_iScriptType; }

public:
    virtual void ScriptTick() {};
    virtual void ScriptFinalTick() {};
};


