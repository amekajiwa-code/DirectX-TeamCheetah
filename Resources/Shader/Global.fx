#ifndef _GLOBAL_FX
#define _GLOBAL_FX

#define SMAP_SIZE 4096
#define SHADOW_EPSILON 0.005f
//ConstantBuffer//
cbuffer GlobalBuffer
{
    matrix V;
    matrix P;
    matrix VP;
    matrix VInv;
};

cbuffer TransformBuffer
{
    matrix W;
};

cbuffer ShadowBuffer
{
    matrix matShadow;
};
//VertexData//
struct Vertex
{
    float4 position : POSITION;
};

struct VertexTexture
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VertexColor
{
    float4 position : POSITION;
    float2 color : COLOR;
};

struct VertexTextureNormal
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct VertexTextureNormalTangent
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    uint instanceID : SV_INSTANCEID;
    matrix world : INST;
};

struct VertexTextureNormalTangentBlend
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 blendIndices : BLEND_INDICES;
    float4 blendWeights : BLEND_WEIGHTS;
    uint instanceID : SV_INSTANCEID;
    matrix world : INST;
};

//VertexOutput//
struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct MeshOutput
{
    float4 position : SV_POSITION;
    float3 worldPosition : POSITION1;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};

struct ShadowOutput
{
    float4 position : SV_POSITION;
    float3 worldPosition : POSITION1;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 texShadow : TEXCOORD1;
};
struct ShadowDepthOutPut
{
    float4 position : SV_POSITION;
    float2 d : TEXCOORD0;
};
//SamplerState//
SamplerState LinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
    AddressW = Wrap;
};

SamplerState PointSampler
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = Wrap;
    AddressV = Wrap;
};

SamplerState ClampLinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Clamp;
    AddressV = Clamp;
    AddressW = Clamp;
};

SamplerState ShadowSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Border;
    AddressV = Border;
    AddressW = Border;
    ComparisonFunc = LESS;
};
//Ra
//RasterizerState//
RasterizerState FillModeWireFrame
{
    FillMode = WireFrame;
};

RasterizerState CullNone
{
    CullMode = None;
};
RasterizerState ShadowRaster
{
    DepthClipEnable = true;
    ScissorEnable = false;
    FillMode = Solid;
    CullMode = Back;
    FillMode = SOLID;
    CullMode = BACK;
    DepthBias = 30000;
    DepthBiasClamp = 3.0f;
    SlopeScaledDepthBias = 1.0f;
};
RasterizerState MollaRaster
{
    DepthClipEnable = true;
    ScissorEnable = false;
    FillMode = Solid;
    CullMode = Back;
};
RasterizerState FrontCounterClockwiseTrue
{
    FrontCounterClockwise = true;
};
//DepthStencilState//
DepthStencilState ShadowDepth
{
    DepthEnable = true;
    DepthWriteMask = ALL;
    DepthFunc = LESS_EQUAL;
    StencilEnable = false;
    StencilReadMask = 1;
    StencilWriteMask = 1;
    FrontFaceStencilFunc = ALWAYS;
    FrontFaceStencilFail = INCR;
    FrontFaceStencilDepthFail = KEEP;
    FrontFaceStencilPass = KEEP;

    BackFaceStencilFail = KEEP;
    BackFaceStencilDepthFail = KEEP;
    BackFaceStencilPass = KEEP;
    BackFaceStencilFunc = ALWAYS;

};
//Macro//

#define PASS_VP(name, vs, ps)						\
pass name											\
{													\
	SetVertexShader(CompileShader(vs_5_0, vs()));	\
	SetPixelShader(CompileShader(ps_5_0, ps()));	\
}

#define PASS_RS_VP(name, rs, vs, ps)				\
pass name											\
{													\
    SetRasterizerState(rs);							\
    SetVertexShader(CompileShader(vs_5_0, vs()));	\
    SetPixelShader(CompileShader(ps_5_0, ps()));	\
}                                                  
#define PASS_RS_SP(name, rs, vs, ps)				\
pass name											\
{													\
    SetRasterizerState(rs);							\
    SetDepthStencilState(ShadowDepth,false);        \
    SetVertexShader(CompileShader(vs_5_0, vs()));	\
    SetPixelShader(CompileShader(ps_5_0, ps()));	\
}                                                   \

#define PASS_RS_DS_VP(name, rs, vs,ps)				\
pass name											\
{													\
    SetRasterizerState(rs);							\
    SetVertexShader(CompileShader(vs_5_0, vs()));	\
    SetPixelShader(CompileShader(ps_5_0, ps()));	\
}                                                   \
//Function//
float3 CameraPosition()
{
    return VInv._41_42_43;
}
#endif
