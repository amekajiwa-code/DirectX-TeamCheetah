#include "Global.fx"

float3 LightDir; //�ݻ籤�� ������ ����
float4 LightSpecular; //�ݻ籤�� ��
float4 MaterialSpecular; //�޾� ���� �� �ִ� ���� ���� (0~1)

Texture2D DiffuseMap;

MeshOutput VS(VertexTextureNormal input)
{
	MeshOutput output;
	output.position = mul(input.position, W);
    output.worldPosition = input.position;
	output.position = mul(output.position, VP);
	

    output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)W);

	return output;
}

//Specular(�ݻ籤)
/*
�� �������� ������ �ݻ�Ǵ� ��(Phong)
*/

float4 PS(MeshOutput input) : SV_TARGET
{
    //float3 R = reflect(LightDir, input.normal);
    float3 R = LightDir - (2 * input.normal * dot(LightDir, input.normal));
    R = normalize(R);
	
    float3 cameraPosition = -V._41_42_43;
    float3 E = normalize(cameraPosition - input.worldPosition);
	//0~1
    float value = saturate(dot(R, E)); 
    float specular = pow(value, 5);
	
    float color = DiffuseMap.Sample(LinearSampler, input.uv);
	color = color * LightSpecular * MaterialSpecular * specular;
	
	return color;
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
};
