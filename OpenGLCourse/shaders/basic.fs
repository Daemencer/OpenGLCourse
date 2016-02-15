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
} IN;

const vec3 lightPos = vec3(0.0, 0.0, 1.0);
const float la = 0.5;
const vec3 ld = vec3(1.0, 1.0, 1.0);
const vec3 ls = vec3(1.0, 1.0, 1.0);

const vec3 Ke = vec3(1.0, 1.0, 1.0);
const vec3 Ka = vec3(1.0, 0.0, 0.0);
const vec3 Kd = vec3(1.0, 1.0, 1.0);
const vec3 Ks = vec3(1.0, 1.0, 1.0);
const float shininess = 0.1;

uniform sampler2D texSampler;

out vec4 Fragment;

void main(void)
{
	vec4 ambientColor = vec4(la * Ka, 0.0);

	vec3 lightDir = normalize(lightPos - IN.v_pos);

	float diffuseCoef = max(dot(IN.v_normal, lightDir), 0.0);
	vec4 diffuseColor = vec4(diffuseCoef * ld, 0.0);
	
	vec4 lightColor = ambientColor + diffuseColor;
	vec4 result = ambientColor * IN.v_fragmentColor;
	Fragment = result * texture(texSampler, IN.v_texCoords);
}