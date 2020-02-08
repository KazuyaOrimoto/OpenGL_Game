// Request GLSL 3.3
#version 330

// Tex coord input from vertex shader
in vec2 fragTexCoord;
// Normal (in world space)
in vec3 fragNormal;
// Position (in world space)
in vec3 fragWorldPos;

// This corresponds to the output color to the color buffer
layout (location = 0) out vec4 outColor0; // 出力先の指定
layout (location = 1) out vec4 outColor1; // 出力先の指定

// This is used for the texture sampling
uniform sampler2D uTexture;
uniform vec3 uHDRColor = vec3(0.0,0.0,0.0);

// Create a struct for directional light
struct DirectionalLight
{
	// Direction of light
	vec3 mDirection;
	// Diffuse color
	vec3 mDiffuseColor;
	// Specular color
	vec3 mSpecColor;
};

// Uniforms for lighting
// Camera position (in world space)
uniform vec3 uCameraPos;
// Specular power for this surface
uniform float uSpecPower;
// Ambient light level
uniform vec3 uAmbientLight;

// Directional Light
uniform DirectionalLight uDirLight;

void main()
{
	// Surface normal
	vec3 N = normalize(fragNormal);
	// Vector from surface to light
	vec3 L = normalize(-uDirLight.mDirection);
	// Vector from surface to camera
	vec3 V = normalize(uCameraPos - fragWorldPos);
	// Reflection of -L about N
	vec3 R = normalize(reflect(-L, N));

	// Compute phong reflection
	vec3 Phong = uAmbientLight;
	float NdotL = dot(N, L);
	if (NdotL > 0)
	{
		vec3 Diffuse = uDirLight.mDiffuseColor * NdotL;
		vec3 Specular = uDirLight.mSpecColor * pow(max(0.0, dot(R, V)), uSpecPower);
		Phong += Diffuse + Specular;
	}

	// Final color is texture color times phong light (alpha = 1)
    outColor0 = texture(uTexture, fragTexCoord) * vec4(Phong, 1.0f);
    outColor1.a = outColor0.a;
    vec3 bright = (outColor0.rgb + uHDRColor) - vec3(1.0,1.0,1.0);
    vec3 col = clamp(bright,vec3(0.0,0.0,0.0),vec3(1.0,1.0,1.0));
    outColor1.rgb = col;
}
