#include "Global.fx"

float3 LightDir; //빛의 방향
float4 LightDiffuse; //분산광의 색
float4 MaterialDiffuse; //받아 들일 수 있는 색의 정도 (0~1)
Texture2D DiffuseMap;

VertexOutput VS(VertexTextureNormal input)
{
	VertexOutput output;
	output.position = mul(input.position, W);
	output.position = mul(output.position, VP);
	output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)W);

	return output;
}


//Diffuse(분산광)
/*
물체의 표면에서 분산되어 눈으로 들어오는 빛
분산 된 각도에 따라 밝기가 다름(람베르트 공식)
*/

float4 PS(VertexOutput input) : SV_TARGET
{
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    float value = dot(-LightDir, input.normal);
    color = color * value * LightDiffuse * MaterialDiffuse;
	
	return color;
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
};
