#ifndef _LIGHT_FX
#define _LIGHT_FX
#include "Global.fx"

//struct
struct LightDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
    float3 direction;
    float  padding;
};
struct MaterialDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
};
//ConstBuffer
cbuffer LightBuffer
{
    LightDesc GlobalLight;
};
cbuffer MaterialBuffer
{
    MaterialDesc Material;
};
//SRV
Texture2D DiffuseMap;
Texture2D SpecularMap;
Texture2D NormalMap;
//Function
float4 ComputeLight(float3 normal, float2 uv, float3 worldPosition)
{
    float4 ambientColor = 0;
    float4 diffuseColor = 0;
    float4 specularColor = 0;
    float4 emissiveColor = 0;
    
    //Ambient
    {
        float4 color = GlobalLight.ambient * Material.ambient;
        ambientColor = DiffuseMap.Sample(LinearSampler, uv) * color;
    }
    //Diffuse
    {
        float4 color = DiffuseMap.Sample(LinearSampler, uv);
        float value = dot(-GlobalLight.direction, normal);
        diffuseColor = color * value * GlobalLight.diffuse * Material.diffuse;
    }
    //Specular
    {
        float3 R = GlobalLight.direction - (2 * normal * dot(GlobalLight.direction, normal));
        R = normalize(R);
        float3 cameraPosition = CameraPosition();
        float3 E = normalize(cameraPosition - worldPosition);
        
        float value = saturate(dot(R, E));
        float specular = pow(value, 5);
	
        specularColor = GlobalLight.specular * Material.specular * specular;
    }
    //Emissive
    {
        float3 cameraPosition = CameraPosition();
        float3 E = normalize(cameraPosition - worldPosition);
	
        float value = saturate(dot(E, normal));
        float emissive = 1.0f - value;

        emissive = smoothstep(0.0f, 1.0f, emissive);
        emissive = pow(emissive, 5);
        
        emissiveColor = GlobalLight.emissive * Material.emissive * emissive;
    }
    
    return ambientColor + diffuseColor + specularColor + emissiveColor;
};
#endif
