#ifndef _STD2D
#define _STD2D

#include "value.fx"

struct VS_IN
{
    float3 LocalPos : POSITION;
    float4 Color   : COLOR;
    float4 UV : TEXCOORD;
};

struct VS_OUT
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.Position = float4(_in.LocalPos, 1.f);
    output.Position.x += TransPosX;
    output.Position.y += TransPosY;
    output.UV = _in.UV;

    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    float4 outputColor;
    
    if (g_btex_0 != 0)
    {
        outputColor = g_tex_0.Sample(g_sam_0, _in.UV);
    }
    
    if (g_btex_1 != 0)
    {
        outputColor = g_tex_1.Sample(g_sam_0, _in.UV);
    }

        return outputColor;
}

#endif