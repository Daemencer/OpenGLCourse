#version 430

struct Light
{
	vec3	position;
	float 	la;
	vec3	ld;
	vec3	ls;
};
//uniform Light	u_directionalLight;

struct Material
{
	vec3 Ke;
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float shininess;
};
//uniform Material u_material;

in VS_OUTPUT
{
	vec3 v_pos;
	vec3 v_normal;
	vec4 v_fragmentColor;
	vec2 v_texCoords;
	
	vec3 v_viewPos;
} IN;

const vec3 lightPos = vec3(0.0, 0.0, 1.0);
const float la = 0.5;
const vec3 ld = vec3(1.0, 0.0, 0.0);
const vec3 ls = vec3(1.0, 1.0, 1.0);

const float specularCoef = 0.5;

const vec3 Ke = vec3(1.0, 1.0, 1.0);
const vec3 Ka = vec3(1.0, 1.0, 1.0);
const vec3 Kd = vec3(1.0, 1.0, 1.0);
const vec3 Ks = vec3(1.0, 1.0, 1.0);
const float shininess = 0.1;

uniform sampler2D texSampler;

out vec4 Fragment;

void main(void)
{
	vec4 ambientColor = vec4(la * Ka, 1.0);
	vec3 normalized_normal = normalize(IN.v_pos);
	//vec3 lightDir = normalize(lightPos - IN.v_pos);
	vec3 lightDir = vec3(0.0, 0.0, 1.0);

	float diffuseCoef = max(dot(normalized_normal, lightDir), 0.0);
	vec4 diffuseColor = vec4(diffuseCoef * ld, 1.0);
	
	vec3 viewDir = normalize(IN.v_viewPos - IN.v_pos);
	vec3 reflectDir = reflect(-lightDir, normalized_normal);
	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec4 specularColor = vec4(specularCoef * spec * ls, 1.0);
	
	vec4 lightColor = ambientColor + diffuseColor + specularColor;
	vec4 result = lightColor * IN.v_fragmentColor;
	Fragment = result * texture(texSampler, IN.v_texCoords);
}