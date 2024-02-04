#include "Global.fx"
#include "Light.fx"
static const int g_iNumTexture = 6;

MeshOutput VS(VertexTextureNormalTangent input)
{
	MeshOutput output;
	output.position = mul(input.position,W);
    output.worldPosition = output.position.xyz;
	output.position = mul(output.position, VP);
	
    output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)W);
    output.tangent = mul(input.tangent, (float3x3)W);
	return output;
}

struct SkyOutput
{
    float4 position : SV_POSITION;
    float3 worldPosition : POSITION1;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    uint PrimitiveID : SV_PrimitiveID;
};

Texture2D p_diffuseArray[g_iNumTexture];

float4 GetTextureColor(uint index, float2 uv)
{
	float4 fColor = float4(1, 1, 1, 1);
	switch (index)
	{
	case 0: fColor = p_diffuseArray[0].Sample(LinearSampler, uv); break;
	case 1: fColor = p_diffuseArray[1].Sample(LinearSampler, uv); break;
	case 2: fColor = p_diffuseArray[2].Sample(LinearSampler, uv); break;
	case 3: fColor = p_diffuseArray[3].Sample(LinearSampler, uv); break;
	case 4: fColor = p_diffuseArray[4].Sample(LinearSampler, uv); break;
	case 5: fColor = p_diffuseArray[5].Sample(LinearSampler, uv); break;
	}
	return fColor;
}
float4 PS(SkyOutput input) : SV_TARGET
{
	uint index = input.PrimitiveID / 2;
	float4 fColor = float4(1, 1, 1, 1);
	fColor = GetTextureColor(index, input.uv);
	return fColor;
}

technique11 T0
{
	PASS_RS_VP(P0,FrontCounterClockwiseTrue, VS, PS)
};
