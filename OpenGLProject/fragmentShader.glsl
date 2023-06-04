#version 430 core

out vec4 FragColor;

in vec2 outUV;

uniform sampler2D ourTexture;

uniform vec3 light_color;
uniform float ambient_strength;

void main()
{
	vec4 ambient = vec4(light_color, 1.0f) * ambient_strength;

	FragColor = ambient * texture(ourTexture, outUV);
};