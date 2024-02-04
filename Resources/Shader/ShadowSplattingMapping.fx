#include "Global.fx"
#include "Light.fx"


Texture2D SplattingMapA;
Texture2D  SplattingMapB;
Texture2D  SplattingMapC;
Texture2D  SplattingMapNormalA;
Texture2D  SplattingMapNormalB;
Texture2D  SplattingMapNormalC;
Texture2D  SplattingAlpha;
Texture2D  DepthMap;
ShadowOutput VS(VertexTextureNormalTangent input)
{
	ShadowOutput output;
	output.position = mul(input.position, W);
    	output.worldPosition = output.position.xyz;
	output.position = mul(output.position, VP);
	
    	output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)W);
    	output.tangent = mul(input.tangent, (float3x3)W);
	output.texShadow = mul(input.position, matShadow );
	return output;
}


float4 PS(ShadowOutput input) : SV_TARGET
{
	//ComputeNormalMapping(input.normal, input.tangent, input.uv);
	
	float4 baseColor = DiffuseMap.Sample(LinearSampler, input.uv*8);
	float4 colorA = SplattingMapA.Sample(LinearSampler, input.uv*8);
	float4 colorB = SplattingMapB.Sample(LinearSampler, input.uv*8);
	float4 colorC = SplattingMapC.Sample(LinearSampler, input.uv*8);
	float4 alpha = SplattingAlpha.Sample(LinearSampler, input.uv);
	float4 finalColor = lerp(baseColor, colorA, alpha.r);
	finalColor = lerp(finalColor, colorB, alpha.g);
	finalColor = lerp(finalColor, colorC, alpha.b);

    	finalColor = ComputeLightMixed(input.normal, input.uv, input.worldPosition,finalColor);
		{
		float LightAmount=1.0f;
		float4 vPosLight = input.texShadow;
		
		for( int iLight=0; iLight < 1; iLight++ )
		{
	        //transform from RT space to texture space.
	        float2 ShadowTexC = vPosLight.xy / vPosLight.w;
	        // transform to texel space
	        float2 texelpos = SMAP_SIZE * ShadowTexC;        
	        // Determine the lerp amounts           
	        float2 lerps = frac( texelpos );
	        //read in bilerp stamp, doing the shadow checks
	        float sourcevals[4];
	        sourcevals[0] = (DepthMap.Sample( ShadowSampler, ShadowTexC ) 
				+ SHADOW_EPSILON < vPosLight.z / vPosLight.w)? 0.0f: 1.0f;  
	        sourcevals[1] = (DepthMap.Sample( ShadowSampler, ShadowTexC 
				+ float2(1.0/SMAP_SIZE, 0) ) + SHADOW_EPSILON < vPosLight.z / vPosLight.w)? 0.0f: 1.0f;  
	        sourcevals[2] = (DepthMap.Sample( ShadowSampler, ShadowTexC 
				+ float2(0, 1.0/SMAP_SIZE) ) + SHADOW_EPSILON < vPosLight.z / vPosLight.w)? 0.0f: 1.0f;  
	        sourcevals[3] = (DepthMap.Sample( ShadowSampler, ShadowTexC 
				+ float2(1.0/SMAP_SIZE, 1.0/SMAP_SIZE) ) + SHADOW_EPSILON < vPosLight.z / vPosLight.w)? 0.0f: 1.0f;  
		        // lerp between the shadow values to calculate our light amount
	        LightAmount = lerp( lerp( sourcevals[0], sourcevals[1], lerps.x ),
	                                  lerp( sourcevals[2], sourcevals[3], lerps.x ),
	                                  lerps.y );
	    } 
	 	finalColor= finalColor*max(0.5f, LightAmount);
	}
	return finalColor;
}

ShadowDepthOutPut SHADOW_VS(VertexTextureNormalTangent input)
{
	
    ShadowDepthOutPut output;
    output.position = mul(float4(input.position), W);
    output.position = mul(output.position, VP);
	
    output.d = output.position.zw;
    return output;
}

float4 PSG(ShadowDepthOutPut input) : SV_TARGET
{
    float shadow = input.d.x / input.d.y;
    return float4(shadow, shadow, shadow, 1.0f);
}

technique11 T0
{
	PASS_VP(P0, VS, PS)

	PASS_RS_SP(P1,ShadowRaster,SHADOW_VS,PSG)

	PASS_RS_DS_VP(P2, ShadowRaster, VS, PS)
};
