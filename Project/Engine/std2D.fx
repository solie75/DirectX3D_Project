#ifndef _STD2D
#define _STD2D

#include "value.fx"

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.Position = mul(float4(_in.LocalPos, 1.f), g_matWVP);
    output.UV = _in.UV;

    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    float4 outputColor = (float4) (1.f, 0.f, 0.f, 1.f);
    
    if (g_btex_0 != 0)
    {
        outputColor = g_tex_0.Sample(anisotropicSampler, _in.UV);
    }
    
    if (g_btex_1 != 0)
    {
        outputColor = g_tex_1.Sample(anisotropicSampler, _in.UV);
    }

    return outputColor;
}

#endif