#pragma once
#include "CRes.h"
#include "ptr.h"
#include "CShader.h"


class CMaterial :
    public CRes
{
private:
    Ptr<CShader> m_pShader;
    //tMtrlConst 
};

