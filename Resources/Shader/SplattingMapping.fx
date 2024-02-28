#include "Global.fx"
#include "Light.fx"

Texture2D SplattingMapA;
Texture2D  SplattingMapB;
Texture2D  SplattingMapC;
Texture2D  SplattingMapNormalA;
Texture2D  SplattingMapNormalB;
Texture2D  SplattingMapNormalC;
Texture2D  SplattingAlpha;
MeshOutput VS(VertexTextureNormalTangent input)
{
	MeshOutput output;
	output.position = mul(input.position, W);
    output.worldPosition = output.position.xyz;
	output.position = mul(output.position, VP);
	
    output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)W);
    output.tangent = mul(input.tangent, (float3x3)W);
	return output;
}


float4 PS(MeshOutput input) : SV_TARGET
{
    ComputeNormalMapping(input.normal, input.tangent, input.uv);
	
	float4 baseColor = DiffuseMap.Sample(LinearSampler, input.uv*8);
	float4 colorA = SplattingMapA.Sample(LinearSampler, input.uv*8);
	float4 colorB = SplattingMapB.Sample(LinearSampler, input.uv*8);
	float4 colorC = SplattingMapC.Sample(LinearSampler, input.uv*8);
	float4 alpha = SplattingAlpha.Sample(LinearSampler, input.uv);
	float4 finalColor = lerp(baseColor, colorA, alpha.r);
	finalColor = lerp(finalColor, colorB, alpha.g);
	finalColor = lerp(finalColor, colorC, alpha.b);

    float4 color = ComputeLightMixed(input.normal, input.uv, input.worldPosition,finalColor);
	//color.w=max(0.7f,color.w);
	//finalColor = finalColor*color.w;
	return finalColor; 
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
};
