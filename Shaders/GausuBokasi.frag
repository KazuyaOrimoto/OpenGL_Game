// Request GLSL 3.3
#version 330

out vec4 outColor;
  
in vec2 fragTexCoord;

uniform sampler2D uTexture;
  
uniform bool horizontal = true;
uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{             
    vec2 tex_offset = 1.0 / textureSize(uTexture, 0); // gets size of single texel
    vec3 result = texture(uTexture, fragTexCoord).rgb * weight[0]; // current fragment's contribution
    if(horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(uTexture, fragTexCoord + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(uTexture, fragTexCoord - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture( uTexture, fragTexCoord + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture( uTexture, fragTexCoord - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    float add = result.x + result.y + result.z;
    if(add < 0.1)
    {
         outColor = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else
    {
         outColor = vec4(result, 0.0);
    }
}