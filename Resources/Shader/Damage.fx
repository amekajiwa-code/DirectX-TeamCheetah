#ifndef _RENDER_FX_
#define _RENDER_FX_
#include "Global.fx"

Texture2D NumListMap[10];
BlendState DamageBlendState
{
    BlendEnable[0] = true;
    SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
    BlendOp = ADD;
    BlendOpAlpha = ADD;
    SrcBlendAlpha = ONE;
    DestBlendAlpha = ZERO;
    RenderTargetWriteMask[0] = 0x0F;
};
//Mesh Render//
struct NumMesh
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    uint instanceID : SV_INSTANCEID;
    matrix world : INST;
    uint num : INSTU;
};
struct NumOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 worldPosition : POSITION1;
    uint num : NUM;
};
NumOutput MeshVS(NumMesh input)
{
    NumOutput output;

    output.position = mul(input.position, input.world);
    output.worldPosition = output.position;
    output.position = mul(output.position, VP);
    
    output.uv = input.uv;
    output.num = input.num;
    
    return output;
}

float4 PS(NumOutput input) : SV_TARGET
{
    float4 color = float4(1, 0, 0, 1);
    switch (input.num)
    {
        case 0:color = NumListMap[0].Sample(LinearSampler, input.uv);break;
        case 1:color = NumListMap[1].Sample(LinearSampler, input.uv);break;
        case 2:color = NumListMap[2].Sample(LinearSampler, input.uv);break;
        case 3:color = NumListMap[3].Sample(LinearSampler, input.uv);break;
        case 4:color = NumListMap[4].Sample(LinearSampler, input.uv);break;
        case 5:color = NumListMap[5].Sample(LinearSampler, input.uv);break;
        case 6:color = NumListMap[6].Sample(LinearSampler, input.uv);break;
        case 7:color = NumListMap[7].Sample(LinearSampler, input.uv);break;
        case 8:color = NumListMap[8].Sample(LinearSampler, input.uv);break;
        case 9:color = NumListMap[9].Sample(LinearSampler, input.uv);break;
    }
    
    return color;
}

technique11 T0
{
    PASS_RS_BS_VP(P0,CullNone,DamageBlendState,MeshVS,PS)
//    PASS_RS_SP(P0, CullNone, MeshVS, PS)
//	PASS_RS_SP(P0, ShadowRaster, MeshVS, PS)
};

#endif
