//=============================================================================
//	@file	BasicMesh.frag
//	@brief	陰影なしのモデルを描画するピクセルシェーダー
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#version 330

in vec2 fragTexCoord;

layout (location = 0) out vec4 outColor0; // 出力先の指定
layout (location = 1) out vec4 outColor1; // 出力先の指定

uniform sampler2D uTexture;
void main()
{
    outColor0 = texture(uTexture, fragTexCoord);
    outColor1 = outColor0;
}
