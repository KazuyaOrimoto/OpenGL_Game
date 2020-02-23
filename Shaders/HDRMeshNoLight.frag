// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330

// Tex coord input from vertex shader
in vec2 fragTexCoord;

// This corresponds to the output color to the color buffer
layout (location = 0) out vec4 outColor0; // 出力先の指定
layout (location = 1) out vec4 outColor1; // 出力先の指定

// This is used for the texture sampling
uniform sampler2D uTexture;
uniform vec3 uHDRColor = vec3(0.0,0.0,0.0);

void main()
{
	// Sample color from texture
    outColor0 = texture(uTexture, fragTexCoord);
    outColor1.a = outColor0.a;
    vec3 bright = (outColor0.rgb + uHDRColor) - vec3(1.0,1.0,1.0);
    vec3 col = clamp(bright,vec3(0.0,0.0,0.0),vec3(1.0,1.0,1.0));
    outColor1.rgb = col;
}