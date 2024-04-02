#ifndef _FUNC
#define _FUNC

#include "value.fx"
#include "struct.fx"

#define DT g_deltaTime
#define AccTime g_AccumulateTime
// ======
// Random
// ======

static float GaussianFilter[5][5] =
{
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.0219f, 0.0983f, 0.1621f, 0.0983f, 0.0219f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
};

void GaussianSample(in Texture2D _NoiseTex, float2 _vResolution, float _NormalizedThreadID, out float3 _vOut)
{
    float2 vUV = float2(_NormalizedThreadID, 0.5f);
    
    vUV.x += AccTime;
    
    // CalCulate Texture's UV on Sin
    // when Period if Trigonometric Functions is 0.2pi x value increased with AccTime; 
    vUV.y -= sin((_NormalizedThreadID - AccTime) * 2.f * 3.1415926535 * 10.f) / 2.f;

    // frac() returns the Decimal fraction of a given number;
    if (1.f < vUV.x)
    {
        vUV.x = frac(vUV.x);
    }
    else if (vUV.x < 0.f)
    {
        vUV.x = 1.f + frac(vUV.x);
    }
    
    if (1.f < vUV.y)
    {
        vUV.y = frac(vUV.y);
    }
    else if (vUV.y < 0.f)
    {
        vUV.y = 1.f + frac(vUV.y);
    }
    
    float2 pixel = vUV * _vResolution;
    float2 offset = float2(-2.f, -2.f);
    float3 vOut = (float3) 0.f;
    
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            vOut += _NoiseTex[pixel + offset + int2(i, j)] * GaussianFilter[i][j];
        }
    }
    _vOut = vOut;
}

#endif