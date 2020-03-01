//=============================================================================
//	@file	Sprite.frag
//	@brief	2Dスプライト用ピクセルシェーダー
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#version 330

in vec2 fragTexCoord;

out vec4 outColor;

uniform sampler2D uTexture;

void main()
{
    outColor = texture(uTexture, fragTexCoord);
}
