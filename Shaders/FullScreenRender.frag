
// Request GLSL 3.3
#version 330

in vec2 TexCoords;
out vec4 color;

// This is used for the texture sampling
uniform sampler2D screenTexture;

void main()
{
    // Sample color from texture
    color = vec4 (1.0,0.0,0.0,1.0);
}
