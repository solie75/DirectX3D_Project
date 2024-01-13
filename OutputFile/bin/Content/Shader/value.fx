
#ifndef _VALUE
#define _VALUE

cbuffer TRANSPOS : register(b0)
{
    float TransPosX;
    float TransPosY;
    float pad1;
    float pad2;
}

Texture2D g_tex_0 : register(t0);
SamplerState g_sam_0 : register(s0);

#endif