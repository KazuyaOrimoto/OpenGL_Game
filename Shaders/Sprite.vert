//=============================================================================
//	@file	Sprite.vert
//	@brief	2Dスプライト用頂点シェーダー
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

// Request GLSL 3.3
#version 330

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

out vec2 fragTexCoord;

void main()
{
	vec4 pos = vec4(inPosition, 1.0);
	gl_Position = pos * uWorldTransform * uViewProj;

	fragTexCoord = inTexCoord;
}
