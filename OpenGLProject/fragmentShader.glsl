#version 430 core

out vec4 FragColor;

in vec2 outUV;

uniform sampler2D ourTexture;

void main()
{
	vec4 sunlight = vec4(0.3f, 0.3f, 0.3f, 1.0f);

	FragColor = texture(ourTexture, outUV) * sunlight;
};