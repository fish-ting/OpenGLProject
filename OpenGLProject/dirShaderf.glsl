#version 430 core

out vec4 FragColor;

in vec2 outUV;
in vec3 outFragPos;
in vec3 outNormal;

uniform sampler2D ourTexture;
uniform vec3 view_pos;

struct Material
{
	sampler2D m_diffuse;
	sampler2D m_specular;

	float m_shiness;
};
uniform Material myMaterial;

struct Light
{
	vec3 m_direction;
	vec3 m_ambient;
	vec3 m_diffuse;
	vec3 m_specular;
};
uniform Light myLight;

void main()
{
	vec3 lDir = normalize(myLight.m_direction);
	vec3 ambient = myLight.m_ambient * vec3(texture(myMaterial.m_diffuse, outUV));

	vec3 _normal = normalize(outNormal);

	float _diff = max(0.0f, dot(_normal, -lDir));
	vec3 _diffuse = myLight.m_diffuse * _diff * vec3(texture(myMaterial.m_diffuse, outUV));

	float _specular_strength = 0.5;
	vec3 _viewDir = normalize(view_pos - outFragPos);
	vec3 _reflectDir = reflect(lDir, outNormal);
	float _spec = pow(max(0.0f, dot(_viewDir, _reflectDir)), myMaterial.m_shiness);
	vec3 _specular = myLight.m_specular * _spec * vec3(texture(myMaterial.m_specular, outUV));

	vec3 result = _diffuse + ambient + _specular;

	FragColor = texture(ourTexture, outUV) * vec4(result, 1.0f);
};