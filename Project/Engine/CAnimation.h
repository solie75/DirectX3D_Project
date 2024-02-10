#pragma once
#include "CRes.h"

class CAnimator;

class CAnimation :
    public CRes
{
private:
    CAnimator* m_pOwner;

};

