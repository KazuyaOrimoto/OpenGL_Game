//=============================================================================
//	@file	HDRMesh.frag
//	@brief	陰影ありのモデルをHDR描画する頂点シェーダー
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#version 330

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;

layout (location = 0) out vec4 outColor0; // 出力先の指定
layout (location = 1) out vec4 outColor1; // 出力先の指定

struct DirectionalLight
{
	vec3 mDirection;
	vec3 mDiffuseColor;
	vec3 mSpecColor;
};


uniform vec3 uCameraPos;
uniform float uSpecPower;
uniform vec3 uAmbientLight;

uniform DirectionalLight uDirLight;

uniform sampler2D uTexture;
uniform vec3 uHDRColor = vec3(0.0,0.0,0.0);


void main()
{
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(-uDirLight.mDirection);
    vec3 V = normalize(uCameraPos - fragWorldPos);
    vec3 R = normalize(reflect(-L, N));

    vec3 Phong = uAmbientLight;
    float NdotL = dot(N, L);
    if (NdotL > 0)
    {
	vec3 Diffuse = uDirLight.mDiffuseColor * NdotL;
	vec3 Specular = uDirLight.mSpecColor * pow(max(0.0, dot(R, V)), uSpecPower);
	Phong += Diffuse + Specular;
    }
    outColor0 = texture(uTexture, fragTexCoord) * vec4(Phong, 1.0f);
    outColor1.a = outColor0.a;
    vec3 bright = (outColor0.rgb + uHDRColor) - vec3(1.0,1.0,1.0);
    vec3 col = clamp(bright,vec3(0.0,0.0,0.0),vec3(1.0,1.0,1.0));
    outColor1.rgb = col;
}
