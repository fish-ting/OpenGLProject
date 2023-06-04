#version 430 core

out vec4 FragColor;

in vec2 outUV;
in vec3 outFragPos;
in vec3 outNormal;

uniform sampler2D ourTexture;

uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;
uniform float ambient_strength;

void main()
{
	vec3 ambient = light_color * ambient_strength;

	vec3 _normal = normalize(outNormal);
	vec3 _lightDir = normalize(light_pos - outFragPos);
	float _diff = max(0.0f, dot(_normal, _lightDir));
	vec3 _diffuse = _diff * light_color;

	float _specular_strength = 0.5;
	vec3 _viewDir = normalize(view_pos - outFragPos);
	vec3 _reflectDir = reflect(-_lightDir, outNormal);
	float _spec = pow(max(0.0f, dot(_viewDir, _reflectDir)), 128);
	vec3 _specular = _specular_strength * _spec * light_color;

	vec3 result = _diffuse + ambient + _specular;

	FragColor = texture(ourTexture, outUV) * vec4(result, 1.0f);
};