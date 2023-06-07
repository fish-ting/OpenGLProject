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

#define MAX_POINT_NUMBER 4

// ƽ�й�
struct DirLight
{
	vec3 m_direction;
	vec3 m_ambient;
	vec3 m_diffuse;
	vec3 m_specular;
};
uniform DirLight _dirLight;

// �۹��
struct SpotLight
{
	vec3 m_pos;
	vec3 m_direction;
	float m_cutOff;
	float m_outCutOff;

	vec3 m_ambient;
	vec3 m_diffuse;
	vec3 m_specular;

	float m_c;
	float m_l;
	float m_q;
};
uniform SpotLight _spotLight;

// ���Դ
struct PointLight
{
	vec3 m_pos;
	vec3 m_ambient;
	vec3 m_diffuse;
	vec3 m_specular;

	float m_c;
	float m_l;
	float m_q;
};
uniform PointLight _pointLight[MAX_POINT_NUMBER];

vec3 calculateDir(DirLight _light, vec3 _normal, vec3 _viewDir)
{
	vec3 _lightDir = normalize(_light.m_direction);
	// ������
	vec3 _ambient = _light.m_ambient * vec3(texture(myMaterial.m_diffuse, outUV));

	// ������
	float _diff = max(0.0f, dot(_normal, -_lightDir));
	vec3 _diffuse = _light.m_diffuse * _diff * vec3(texture(myMaterial.m_diffuse, outUV));
	
	// ���淴��
	vec3 _reflectDir = reflect(_lightDir, _normal);
	float _spec = pow(max(0.0f, dot(_reflectDir, _viewDir)), myMaterial.m_shiness);
	vec3 _specular = _light.m_specular * _spec * vec3(texture(myMaterial.m_specular, outUV));
	
	return _ambient + _diffuse + _specular;
}

vec3 calculatePoint(PointLight _light, vec3 _normal, vec3 _viewDir, vec3 _fragPos)
{
	vec3 _lightDir = normalize(_fragPos - _light.m_pos);
	// ������
	vec3 _ambient = _light.m_ambient * vec3(texture(myMaterial.m_diffuse, outUV));

	// ������
	float _diff = max(0.0f, dot(_normal, -_lightDir));
	vec3 _diffuse = _light.m_diffuse * _diff * vec3(texture(myMaterial.m_diffuse, outUV));
	
	// ���淴��
	vec3 _reflectDir = reflect(_lightDir, _normal);
	float _spec = pow(max(0.0f, dot(_reflectDir, _viewDir)), myMaterial.m_shiness);
	vec3 _specular = _light.m_specular * _spec * vec3(texture(myMaterial.m_specular, outUV));
	
	// ˥��ϵ������
	float _dist = length(_light.m_pos - _fragPos);
	float _attenuation = 1.0f / (_light.m_c + _light.m_l * _dist + _light.m_q * _dist * _dist);

	return (_ambient + _diffuse + _specular) * _attenuation;
}

vec3 calculateSpot(SpotLight _light, vec3 _normal, vec3 _viewDir, vec3 _fragPos)
{
	vec3 _lightDir = normalize(_fragPos - _light.m_pos);
	vec3 _spotDir = normalize(_light.m_direction);
	float _cosTheta = dot(-_lightDir, -_spotDir);
	float _epsilon = _light.m_cutOff - _light.m_outCutOff;
	float _intensity = clamp((_cosTheta - _light.m_outCutOff) / _epsilon, 0.0f, 1.0f);
	// ������
	vec3 _ambient = _light.m_ambient * vec3(texture(myMaterial.m_diffuse, outUV));

	// ������
	float _diff = max(0.0f, dot(_normal, -_lightDir));
	vec3 _diffuse = _light.m_diffuse * _diff * vec3(texture(myMaterial.m_diffuse, outUV));
	
	// ���淴��
	vec3 _reflectDir = reflect(_lightDir, _normal);
	float _spec = pow(max(0.0f, dot(_reflectDir, _viewDir)), myMaterial.m_shiness);
	vec3 _specular = _light.m_specular * _spec * vec3(texture(myMaterial.m_specular, outUV));
	
	// ˥��ϵ������
	float _dist = length(_light.m_pos - _fragPos);
	float _attenuation = 1.0f / (_light.m_c + _light.m_l * _dist + _light.m_q * _dist * _dist);

	return (_ambient + _diffuse + _specular) * _attenuation * _intensity;
}

void main()
{
	vec3 _normal = normalize(outNormal);
	vec3 _viewDir = normalize(view_pos - outFragPos);
	vec3 _result = calculateDir(_dirLight, _normal, _viewDir);

	for (int i = 0; i < MAX_POINT_NUMBER; i++)
	{
		_result += calculatePoint(_pointLight[i], _normal, _viewDir, outFragPos);
	}

	_result += calculateSpot(_spotLight,  _normal, _viewDir, outFragPos);

	FragColor = vec4(_result, 1.0f);
}