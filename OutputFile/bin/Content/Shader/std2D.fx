#ifndef _STD2D
#define _STD2D

#include "value.fx"

struct VS_IN
{
    float3 LocalPos : POSITION;
    float4 Color : COLOR;
};

struct VS_OUT
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.Position = float4(_in.LocalPos, 1.f);
    output.Position.x += TransPosX;
    output.Position.y += TransPosY;
    output.Color = _in.Color;
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    return _in.Color;
}

#endif