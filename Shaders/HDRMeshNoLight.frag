//=============================================================================
//	@file	HDRMeshNoLight.frag
//	@brief	陰影なしのモデルをHDR描画するピクセルシェーダー
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#version 330

in vec2 fragTexCoord;

layout (location = 0) out vec4 outColor0; // 出力先の指定
layout (location = 1) out vec4 outColor1; // 出力先の指定

uniform sampler2D uTexture;
uniform vec3 uHDRColor = vec3(0.0,0.0,0.0);

void main()
{
    outColor0 = texture(uTexture, fragTexCoord);
    outColor1.a = outColor0.a;
    vec3 bright = (outColor0.rgb + uHDRColor) - vec3(1.0,1.0,1.0);
    vec3 col = clamp(bright,vec3(0.0,0.0,0.0),vec3(1.0,1.0,1.0));
    outColor1.rgb = col;
}
