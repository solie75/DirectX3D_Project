#ifndef _ANIMATION2D
#define _ANIMATION2D

#include "value.fx"

VS_OUT VS_Ani2D(VS_IN _in)
{
    VS_OUT Out = (VS_OUT) 0.0f;

    float4 world = mul(float4(_in.LocalPos, 1.0f), g_matWorld);
    float4 view = mul(world, g_matView);
    float4 proj = mul(view, g_matProj);
    
    Out.Position = proj;
    Out.UV = _in.UV;
    
    return Out;
}

float4 PS_Ani2D(VS_OUT _in) : SV_TARGET
{
    float4 color = (float4) 0.f;

    float2 modifiedTexcoord = _in.UV;
    
    if(SpriteNum > 10)
    {
        modifiedTexcoord.x /= 10.f;
        modifiedTexcoord.x += ((CurSpriteNum - 1) % 10) * 0.1f;
    
        modifiedTexcoord.y /= (((SpriteNum - 1) / 10) + 1);
        modifiedTexcoord.y -= (1.f / (((SpriteNum - 1) / 10) + 1)) * ((CurSpriteNum - 1) / 10);
    }
    else
    {
        modifiedTexcoord.x /= SpriteNum;
        modifiedTexcoord.x += ((CurSpriteNum - 1) % SpriteNum) * (1.f / SpriteNum);
    }
    
    color = atlasTexture.Sample(pointSampler, modifiedTexcoord);
    return color;
}

#endif