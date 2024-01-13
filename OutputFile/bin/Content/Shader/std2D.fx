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
    //output.Color = _in.Color;
    output.UV = _in.UV;

    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    float4 outputColor;

outputColor = g_tex_0.Sample(g_sam_0, _in.UV);

 //   if (g_tex_0)
 //   {
 //       outputColor = g_tex_0.Sample(g_sam_0, _in.UV);
 //   }
 //   else
 //   {
 //       outputColor = float4(1.f, 0.f, 0.f, 1.f);
 //}

    return outputColor;
}

#endif